#include <socket.hpp>
#include <sys/time.h>

Socket::Socket(std::string siteName) :
    siteName(siteName)
{
    // Проверку ошибок как-нибудь бы добавить нормальную
    initSocket();
    tcpConnect();
}

int Socket::dnsResolve()
{
    int status;

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;                // Хоть IPv4, хоть IPv6
    hints.ai_socktype = SOCK_STREAM;            // TCP-соединение

    if((status = getaddrinfo(siteName.c_str(), "http", &hints, &serverInfo)) != 0)
    {
        return status;
    }

    return 0;
}

int Socket::makeNonBlocking()
{
    int status;

    // Делаем неблокирующим
    if((status = fcntl(sock, F_SETFL, O_NONBLOCK)) != 0)
    {
        return status;
    }

    return 0;
}

int Socket::initSocket()
{
    int dnsResolveStatus = dnsResolve();
    if(dnsResolveStatus)                   // ДНС-ошибка
    {
        fprintf(stderr, "Getaddrinfo error: %s, check %s to correctness\n", gai_strerror(dnsResolveStatus), siteName.c_str());
        return dnsResolveStatus;
    }

    sock = socket(serverInfo->ai_family, serverInfo->ai_socktype, serverInfo->ai_protocol);
    if(sock < 0)
    {
        perror("Socket error");
        return 1;
    }

    int nonBlockingStatus = makeNonBlocking();
    if(nonBlockingStatus)
    {
        perror("Couldn`t set socket nonblocking");
        return nonBlockingStatus;
    }

    return 0;
}

int Socket::tcpConnect()
{
    // Установка tcp-соединения
    int ress = connect(sock, serverInfo->ai_addr, serverInfo->ai_addrlen) ;
    if(ress < 0 && errno != EINPROGRESS)
    {
        perror("Connect problem");
        return 1;
    }

    return 0;
}

int Socket::getSock() const
{
    return sock;
}

int Socket::sendFullMessage(std::string message) const
{
   int totalSended = 0;
   int sended = 0;
   int messageLength = message.length();

   // Отправляем, пока не улетит всё сообщение
   while(totalSended < messageLength)
   {
       sended = send(sock, message.c_str() + totalSended, messageLength - totalSended, 0);
       if(sended == -1)
       {
           break;
       }
       totalSended += sended;
   }

   return sended < 0 ? -1 : totalSended;
}

void Socket::setSiteName(std::string & siteName)
{
    siteName = siteName;
}
