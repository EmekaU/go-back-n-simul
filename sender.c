/*
    Author - Emeka V Umeozo [cvu302, 11249945]
*/

#include "imports.h"
#include "ports.h"

int sockfd, server_socket;
struct addrinfo *addr_info_list; /* Linked list of addrinfo structs referenced here */

int window_size;
int upper_edge = 0; /* Append after sending ack (retransmissions don't count)*/
int lower_edge = 0; /* Append after ack received */
int last_acknowledged_seq = -1;
int SEQ = iSEQ_NO; /* sequence count */

frame* sending_window;
struct addrinfo receiver_address;
struct timeval tv;

void run_sender();
char* get_message();
int create_frame_and_send(char* msg);
void retransmit_oldest_frame();
void receive_acks();

void
init_sender(char* hostname, char* port){

    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /* unspecified - both ipv4 or ipv6 accepted */
    hints.ai_socktype = SOCK_DGRAM; /* udp */

    status = getaddrinfo(hostname, port, &hints, &addr_info_list);

    sockfd = get_socket(status, addr_info_list, &receiver_address, false);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /* unspecified - both ipv4 or ipv6 accepted */
    hints.ai_socktype = SOCK_DGRAM; /* udp */

    status = getaddrinfo(hostname, port, &hints, &addr_info_list);

    sockfd = get_socket(status, addr_info_list, &receiver_address, true);

    printf("Connecting to server at: %s, port: %s\n", hostname, port);
}

void run_sender(){

    fd_set readfds;
    int fdmax;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(sockfd, &readfds);

    fdmax = sockfd;
    printf("Size of sending window: %lu, MWS: %d\n", sizeof sending_window, window_size);
    printf("Enter Message:\n");

    for (int i = 0; i < window_size; i++)
    {
        set_frame_to_default(&sending_window[i]);
    }

    for (;;){

        // TODO: do i add a time out to select? &tv in last param
        if(select(fdmax+1, &readfds, NULL, NULL, NULL) == -1){

            perror("select");
            exit(4);
        }
        
        if (FD_ISSET(sockfd, &readfds)){ /* Returns true if socket fd is ready to be read */
            
            printf("Waiting to receive...\n");
            receive_acks();
        }

        if(FD_ISSET(STDIN_FILENO, &readfds)){

            char* msg = get_message();
            create_frame_and_send(msg);
            printf("Enter Message:\n");
        }
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
        for (i=0; i<window_size; i++) {
            if(sending_window[i].seq == -1){ /* find 1st frame with no valid seq number */

                sending_window[i].seq = SEQ;
                strcpy(sending_window[i].data, msg);
                trim(sending_window[i].data);
                sending_window[i].creation_time = getTime();

                printf("frame seq: %d\n", sending_window[i].seq);
                printf("Frame successfully added to window\n");
                printf("%hhu\n", receiver_address.ai_addr->sa_family);
                send_packet(sockfd, &sending_window[i], sizeof sending_window[i], receiver_address.ai_addr, receiver_address.ai_addrlen);

                upper_edge ++;
                SEQ++;
                return EXIT_SUCCESS;
            }
        }
    }
    
    return EXIT_FAILURE;
}

void receive_acks(){ // receiver would ask for next seq number.

    int num_bytes;
    struct sockaddr_storage incoming_addr;
    uint addr_length = sizeof incoming_addr;
    int ack; // acknowledgement - represented as next sequence number
    int number_of_frames_to_remove;

    if((num_bytes = recvfrom(sockfd, &ack, sizeof(ack), 0, (struct sockaddr *)&incoming_addr, &addr_length)) > 0){
        ack = ntohl(ack);
        printf("ack: %d\n", ack);
        int next_seq = ack % window_size;

        printf("ack :%d\n", ack);
        printf("seq: %d\n", next_seq);
        printf("num bytes: %d\n", num_bytes);

        number_of_frames_to_remove = (next_seq-1) - last_acknowledged_seq;

        for (int i = 0; i < number_of_frames_to_remove; i++){

            printf("Removing frame with seq: %d", sending_window[i].seq);
            // remove from window
            set_frame_to_default(&sending_window[0]);
            lower_edge++;
        }

        last_acknowledged_seq = next_seq-1;
        shift_left(number_of_frames_to_remove, window_size, sending_window);

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

    tv.tv_sec = atoi(argv[4]); /* seconds */     /* do check for sMax and timeout */
    tv.tv_usec = 0;

    init_sender(hostname, port);
    run_sender();
    freeaddrinfo(addr_info_list);
}
