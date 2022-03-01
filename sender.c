/*
    Author - Emeka V Umeozo [cvu302, 11249945]
*/

#include "imports.h"
#include "ports.h"
#include <pthread.h>

int sockfd;
struct addrinfo *addr_info_list; /* Linked list of addrinfo structs referenced here */
struct addrinfo* receiver_address;

frame* sending_window;
int window_size;
int upper_edge = 0; /* Append after sending ack (retransmissions don't count)*/
int lower_edge = 0; /* Append after ack received */
int SEQ = iSEQ_NO; /* sequence count */

uint timeout;
pthread_t worker;
pthread_mutex_t mutex;

void run_sender();
char* get_message();
int create_frame_and_send(char* msg);
void* retransmit_oldest_frame();
void receive_acks();

void init_sender(char* hostname, char* port){

    int status;
    struct addrinfo hints;

    // Setup receiver address info
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /* unspecified - both ipv4 or ipv6 accepted */
    hints.ai_socktype = SOCK_DGRAM; /* udp */

    status = getaddrinfo(hostname, port, &hints, &addr_info_list);
    sockfd = get_socket(status, addr_info_list, &receiver_address, false);
    printf("Connecting to server at: %s, port: %s\n", hostname, port);
}

void run_sender(){

    fd_set readfds, currentfds;
    int fdmax;

    fdmax = sockfd;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(sockfd, &readfds);

    for (int i = 0; i < window_size; i++)
    {
        set_frame_to_default(&sending_window[i]);
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&worker, NULL, retransmit_oldest_frame, NULL);
    for (;;){

        currentfds = readfds;
        if(select((fdmax+1), &currentfds, NULL, NULL, NULL) == -1){

            perror("select");
            exit(4);
        }
        
        if (FD_ISSET(sockfd, &currentfds)){ /* Returns true if socket fd is ready to be read */
            
            receive_acks();
        }

        if(FD_ISSET(STDIN_FILENO, &currentfds)){
            char* msg = get_message();
            create_frame_and_send(msg);
        }

        FD_ZERO(&currentfds);
    }
}

void* retransmit_oldest_frame(){

    struct timeval current_time;

    for (;;) {
        current_time = getTime();
        pthread_mutex_lock(&mutex);
        for (int i = 0; i < window_size; i++) {

            int time_diff = current_time.tv_sec - sending_window[i].time.tv_sec;
            if ((time_diff >= timeout) && (sending_window[i].sent == true)){
                printf("Retransmitting frame with seq = %d\n", sending_window[i].seq);
                sending_window[i].time = getTime();
                send_packet(sockfd, &sending_window[i], sizeof sending_window[i], receiver_address->ai_addr, receiver_address->ai_addrlen);
            }
        }
        pthread_mutex_unlock(&mutex);
    }
}

char*
get_message(){

    size_t max_line_length = MAX_MSG_LEN;
    char* line;
    getline(&line, &max_line_length, stdin);
    return line;
}

int
create_frame_and_send(char* msg){

    size_t i;

    if ((upper_edge - lower_edge) < window_size){ // if window isn't full of unacknowledged frames
        pthread_mutex_lock(&mutex);
        for (i=0; i<window_size; i++) {
            if(sending_window[i].seq == -1){ /* find 1st frame with no valid seq number */

                sending_window[i].seq = SEQ;
                strcpy(sending_window[i].data, msg);
                sending_window[i].time = getTime();
                trim(sending_window[i].data);
                sending_window[i].sent = true;

                send_packet(sockfd, &sending_window[i], sizeof sending_window[i], receiver_address->ai_addr, receiver_address->ai_addrlen);

                upper_edge ++;
                SEQ++;

                pthread_mutex_unlock(&mutex);

                return EXIT_SUCCESS;
            }
        }
    }else{
        printf("Cant add: Window frame is currently full\n");
    }

    return EXIT_FAILURE;
}

void receive_acks(){ // receiver would ask for next seq number.

    struct sockaddr_storage incoming_addr;
    uint addr_length = sizeof incoming_addr;
    int ack; // acknowledgement - represented as next sequence number
    int last_acknowledged_seq, count;

    if(recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&incoming_addr, &addr_length) > 0){
        last_acknowledged_seq = ntohl(ack)-1;
        count = 0; // Also represents number of frames to remove
        pthread_mutex_lock(&mutex);

        for (int i = 0; i < window_size; i++) {

            if ((sending_window[i].seq <= last_acknowledged_seq) &&(sending_window[i].seq >= 0)){

                printf("ACK received! Removing frame with seq = %d\n", sending_window[i].seq);
                // remove from window
                set_frame_to_default(&sending_window[i]);
                lower_edge++;
                count ++;
            }
        }

        shift_left(count, window_size, sending_window);
        pthread_mutex_unlock(&mutex);

    }else{

        close(sockfd);
        free(sending_window);
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char* argv[]){

    char* port;
    char* hostname;

    if(argc != 5){
        printf("Error: This program requires 5 arguments. You supplied %d\n \
				Please try again with: ./sender [receiver's hostname name] [receiver's port #] [window size] [timeout(s)]\n", argc);
        exit(EXIT_FAILURE);
    }

    hostname = argv[1];
    port = argv[2];

    /* Validate remote server's ports range */
    if(!port_is_valid(port)){
        
        printf("Error: port numbers must range between %s and %s\n", MIN_PORT_NO, MAX_PORT_NO);
        exit(EXIT_FAILURE);
    }

    window_size = atoi(argv[3]);
    sending_window = (frame*)malloc(sizeof(frame) * window_size);

    timeout = atoi(argv[4]);

    init_sender(hostname, port);
    run_sender();
}
