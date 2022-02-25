/*
    Author - Emeka V Umeozo [cvu302, 11249945]
*/

#include "imports.h"
#include "ports.h"

int get_socket(int addrinfo_status, struct addrinfo* addr_info_list, struct addrinfo* address, bool is_host){

    int sockfd;
    struct addrinfo *addr_ref;
    int reuse_socket = 1;

    if(addrinfo_status != 0){

        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(addrinfo_status));
        exit(EXIT_FAILURE);
    }

    /* Loop through linkedlist, find first bindable address */
    for(addr_ref = addr_info_list; addr_ref != NULL; addr_ref = addr_ref->ai_next){

        /* get sockfd via socket call with domain, type, and protocol*/
        sockfd = socket(addr_ref->ai_family, addr_ref->ai_socktype, addr_ref->ai_protocol);
        if(sockfd == -1){
            perror("invalid socket\n");
            continue;
        }

        printf("is host: %d\n", is_host);
        if (is_host == true){
            printf("binding socket %d to port\n", sockfd);
            if(bind(sockfd, addr_ref->ai_addr, addr_ref->ai_addrlen) == -1){
                /**
                 * Bind to associate port with the socket file descriptor, addr ref and length of ref in bytes
                 * kernel will associate sockfd with the port in the addrinfo struct
                 */
                close(sockfd); /* close file descriptor */
                perror("server: bind\n");
                continue;
            }

            if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse_socket, sizeof reuse_socket) == -1){
                perror("server: setsockopt\n");
                continue;
            }
        }
        break;
    }

    if(addr_ref == NULL){
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if(address != NULL){

        (*address).ai_addr = addr_ref->ai_addr;
        (*address).ai_canonname = addr_ref->ai_canonname;
        (*address).ai_addrlen = addr_ref->ai_addrlen;
        (*address).ai_family = addr_ref->ai_family;
        (*address).ai_flags = addr_ref->ai_flags;
        (*address).ai_next = addr_ref->ai_next;
        (*address).ai_protocol = addr_ref->ai_protocol;
        (*address).ai_socktype = addr_ref->ai_socktype;
    }

//    freeaddrinfo(addr_info_list);

    return sockfd;
}

/**
 * Send DGRAM packets
 * @return
 */
int send_packet(int socket, void* packet, int packet_size, struct sockaddr* incoming_addr, socklen_t addr_length){
    int num_bytes;
    if((num_bytes = sendto(socket, packet, packet_size, 0, incoming_addr, addr_length)) == -1){
        close(socket);
        fprintf(stderr, "udp: can't send\n");
    }

    printf("num_byes = %d\n", num_bytes);

    return num_bytes;
}

 /* Get sockaddr, IPv4 or IPv6:
 */
void *get_in_addr(struct sockaddr *sa) {

    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((struct sockaddr_in6*)sa)->sin6_addr); 
}

char* get_host_name(){
    char hostname[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    // printf("Hostname: %s\n", hostname);
    struct hostent* h;
    h = gethostbyname(hostname);

    return h->h_name;
}

/**
 * Validates port number entry
 * */
bool port_is_valid(char* port){

	if (atoi(port) < atoi(MIN_PORT_NO) || atoi(port) > atoi(MAX_PORT_NO)){
		return false;
	}
	return true;
}

/**
 * Remove leading and trailing white space characters
 */
void trim(char * str)
{
    int index, i;

    /*
     * Trim leading white spaces
     */
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n')
    {
        index++;
    }

    /* Shift all trailing characters to its left */
    i = 0;
    while(str[i + index] != '\0')
    {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; /* Terminate string with NULL*/


    /*
     * Trim trailing white spaces
     */
    i = 0;
    index = -1;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }

        i++;
    }

    /* Mark the next character to last non white space character as NULL */
    str[index + 1] = '\0';
}

struct timeval getTime(){

    struct timeval time;
    gettimeofday(&time, 0);

    printf("time: %lu\n", time.tv_sec);
    return time;
}

void set_frame_to_default(frame* f){
    struct timeval time;
    time.tv_sec = 0;
    f->seq = -1;
    f->creation_time = time;
    strcpy(f->data, "");
}

void print_frame(frame* f){

    printf("Frame Info: %d\n", f->seq);
    printf(" Sequence number: %d\n", f->seq);
    printf(" Creation time: %lu\n", f->creation_time.tv_sec);
    printf(" Data: %s\n", f->data);
}

void shift_left(int N, int length, frame* window){

    int i, j;
    for (i = 0; i < N; i++){
        
        frame temp = window[0];

        for (j = 0; j < length; j++){
            window[j] = window[j + 1];
        }
        
        window[length-1] = temp;
    }    
}
