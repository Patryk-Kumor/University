// Patryk Kumor
// indeks: 292601
#include "traceroute.h"

int main(int argc, char* argv[]) try
{
    // Sprawdzanie liczby argumentów
    if (argc != 2)
    {
        throw runtime_error("Nieprawidłowa liczba argumentów"); 
    }
    // Tworzenie socketów wymaga sudo
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) 
    {
        throw runtime_error("Socket error, może brakuje sudo?"); 
    }
    // Struct ip socketu
    struct sockaddr_in address;
    // Zerowanie bitów na całym strucie
    bzero(&address, sizeof(address)); 
    // "Address family or format of the socket address" - AF_INET
    address.sin_family = AF_INET; 
    // Konwertuje IP z tekstu do formatu binarnego, jeśli się nie uda (czyli ip jest nieporpawne) - zwraca 0
    if (inet_pton(AF_INET, argv[1], &address.sin_addr) == 0)
    {
       throw runtime_error("IP error, może adres jest niepoprawny?"); 
    }
    // Unikalny id procesu w celu identyfikacji requestów i odpowiedzi
    int process_id = getpid();
    // Główny traceroute
    for (int ttl = 1; ttl <= 30; ttl++)
    {
        // Oznaczenie czasu
        struct timeval tvalBefore;
        gettimeofday (&tvalBefore, NULL);
        // Wysyłanie 3 requestów o tym samym ttlu
        send(sockfd, ttl, process_id, address);
        // Odbieranie odpowiedzi
        if (receive(sockfd, ttl, process_id, tvalBefore)) 
        {
            break;
        }
    }
    // Koniec pracy
    //cout << "ZAKOŃCZONO\n";
    return 0;
}
catch (const exception& e) 
{
    // Cach powinien również wyłapać błędy w funkcjach bibliotecznych
    cout << ">> Program zamknięto <<\nerror: " << e.what() << "\n";
    return -1;
}
