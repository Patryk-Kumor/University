// Patryk Kumor
// indeks: 292601
#include "traceroute.h"

// Checksum pakietów zgodnie z wykładem
u_int16_t compute_icmp_checksum (const void *buff, int length)
{
    u_int32_t sum;
    const u_int16_t* ptr = (const u_int16_t*) buff;
    assert (length % 2 == 0);
    for (sum = 0; length > 0; length -= 2)
    {
        sum += *ptr++;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t)(~(sum + (sum >> 16)));
}

// Wysyłanie pojedyńczego pakietu zgodnie z wykładem
int single_send(int sockfd, int process_id, int ttl, struct sockaddr_in address, int i)
{
    // Tworzenie nagłówka (wystarczy do echo)
    struct icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;
    icmp_header.code = 0;
    icmp_header.un.echo.id = process_id; // Unikalny dla instancji programu
    icmp_header.un.echo.sequence = (ttl - 1)*3 + i; // Unikalny dla wszystkch pakietów 0-89
    icmp_header.checksum = 0;
    icmp_header.checksum = compute_icmp_checksum ((u_int16_t*)&icmp_header, sizeof(icmp_header));
    // Wysyłanie
    if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    {
        throw runtime_error("Setsockopt error, błąd manipulacji ustawień"); 
    }
    if (sendto(sockfd, &icmp_header, sizeof(icmp_header), 0, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        throw runtime_error("Sendto error, nie wysłano pakietu");
    }
    return 1;
}

// Wysyłanie trzech pakietów
void send(int sockfd, int ttl, int process_id, struct sockaddr_in address)
{
    for(int i = 0; i < 3; i++)
    {
        single_send(sockfd, process_id, ttl, address, i);
    }
}
