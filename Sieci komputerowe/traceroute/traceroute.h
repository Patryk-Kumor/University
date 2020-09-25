// Patryk Kumor
// indeks: 292601
#ifndef traceroute_h
#define traceroute_h
#include <iostream>
#include <netinet/ip_icmp.h> // header
#include <netinet/ip.h> // sockety
#include <arpa/inet.h> // sockety
#include <sys/time.h> // time
#include <cassert>
#include <stdint.h> 
#include <string.h>
#include <errno.h>
#include <unistd.h> // getpid
#include <sys/types.h> 

pid_t getpid(void);
// Struktura przechowująca potrzebne nam info. o pakietach
typedef struct packet_info
{
    char *ip;
    int id;
    int ttl;
    int seq;
    long int time;
    bool dest;
} packet_info;
// Send
u_int16_t compute_icmp_checksum (const void *buff, int length);
int single_send(int sockfd, int ttl, int process_id, struct sockaddr_in address);
void send(int sockfd, int ttl, int process_id, struct sockaddr_in address);
// Receive
packet_info get_packet(int sockfd, struct timeval);
int receive(int sockfd, int ttl, int process_id, struct timeval start_time);
using namespace std;
#endif
