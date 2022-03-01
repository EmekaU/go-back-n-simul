// Author - Emeka Umeozo

#ifndef IMPORTS_H
#define IMPORTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define BACKLOG 10
#define iSEQ_NO 0 /* initial sequence number*/
#define MAX_MSG_LEN 256

typedef struct frame{

    /* header */
    int seq;
    bool sent;
    struct timeval time;
    /* data */
    char data[MAX_MSG_LEN];
}frame;

int get_socket(int addrinfo_status, struct addrinfo* addr_info_list, struct addrinfo** address, bool is_host);
int send_packet(int socket, void* packet, int packet_size, struct sockaddr* incoming_addr, socklen_t addr_length);
char* get_host_name();
void print_frame(frame* f);

void set_frame_to_default(frame* f);
void shift_left(int count, int length, frame* arr);

struct timeval getTime();
bool port_is_valid(char* port);
void trim(char * str);
#endif
