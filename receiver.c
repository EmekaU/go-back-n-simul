/*
    Author - Emeka V Umeozo [cvu302, 11249945]
*/

#include "imports.h"
#include "ports.h"


int sockfd;
struct addrinfo *addr_info_list; /* Linked list of addrinfo structs referenced here */
struct addrinfo* host_address;

int next_seq_num = 0;

struct sockaddr_storage incoming_addr;
uint addr_length = sizeof incoming_addr;

void init_receiver();
int run_receiver();
void process_frame(frame* f);
int corruption_test(char* action);
void send_acknowledgement(int next_expected_sequence);

void init_receiver(char* port){

    int status;
    struct addrinfo hints;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /* unspecified - both ipv4 or ipv6 accepted */
    hints.ai_socktype = SOCK_DGRAM; /* udp */
    hints.ai_flags = AI_PASSIVE; /* need to bind to sockfd, fill in ip for me */

    /* get hostname */
    status = getaddrinfo(NULL, port, &hints, &addr_info_list);

    sockfd = get_socket(status, addr_info_list, &host_address, true);
}

int run_receiver(){

    int fd_max;
    frame new_frame;

    fd_set readfds, currentfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd, &readfds);
    fd_max = sockfd;

    for (;;){

        currentfds = readfds;
        if(select(fd_max+1, &currentfds, NULL, NULL, NULL) == -1){

            perror("select");
            exit(4);
        }

        if (FD_ISSET(sockfd, &currentfds)){ /* Returns true if socket fd is ready to be read */
            memset(&new_frame, 0, sizeof new_frame);
            if(recvfrom(sockfd, &new_frame, sizeof new_frame, 0, (struct sockaddr* )&incoming_addr, &addr_length) > 0){

                printf("Frame Received!\n");
                print_frame(&new_frame);
                process_frame(&new_frame);
            }
            else{
                printf("Receiver: Couldn't receive\n");
            }
        }
        FD_ZERO(&currentfds);
    }
}

void process_frame(frame* f){

    if(corruption_test("receiving frame") == 0){ /* If "Y" is entered*/

        if(f->seq == next_seq_num){ // If frame seq is the next expected sequence
            next_seq_num = f->seq + 1;
        }

        if(f->seq <= next_seq_num){ // If frame seq is the next expected sequence or frame is a retransmission
            send_acknowledgement(next_seq_num);
        }
        else{
            printf("%s\n", "Frame sequence number is not the next order sequence. Frame dropped.\n");
        }
    }else{
        printf("%s\n", "Frame is deemed to be corrupted");
    }
}

void send_acknowledgement(int next_expected_sequence){

    int seq = ntohl(next_expected_sequence);
    if(corruption_test("sending ACK") == 0){ /* If "Y" is entered*/
        send_packet(sockfd, &seq, sizeof seq, (struct sockaddr *)&incoming_addr, addr_length);
    }else{
        printf("ack %d is deemed to be corrupted on transit\n", next_expected_sequence);
    }
}


int corruption_test(char* action){
    
    size_t line_length = 10;
    char input[line_length];

    printf("--- Corruption Simulation: %s ---\n", action);
    printf(" Enter 'Y' to make frame valid\n");
    if(fgets(input, line_length, stdin) == NULL){

        printf("Issue with simulation check\n");
    }else{

        if(input[0] == 'Y'){ /* If frame passed (ie: "Y" is entered)*/
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]){

    char* port;

    if(argc != 2){
        printf("Error: This program requires 2 arguments. You supplied %d\n\
				Please try again with: ./receiver [port #]\n", argc);
        exit(EXIT_SUCCESS);
    }

    port = argv[1];
    /* Validate remote server's ports range */
    if(!port_is_valid(port)){
        
        printf("Error: port numbers must range between %s and %s\n", MIN_PORT_NO, MAX_PORT_NO);
        exit(EXIT_FAILURE);
    }

    printf("*** UDP Server *** \n> Machine: %s\n> Port: %s\n\n", get_host_name(), port);

    init_receiver(port);
    run_receiver();
    freeaddrinfo(addr_info_list);

    return 0;
}
