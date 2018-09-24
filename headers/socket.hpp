#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <fcntl.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <iostream>

class Socket
{
public:
    Socket(std::string siteName);
    Socket();
    int tcpConnect();               // По этому будем проверять время коннекта
    void setSiteName(std::string &siteName);

    int getSock() const;
    int sendFullMessage(std::string msg) const;
private:
    int sock;                       // Непосредственно сам дескриптор
    std::string siteName;           // Сокет будет работать с конкретным сайтом
    struct addrinfo *serverInfo;    // Структура, хранящая данные о сервере

    int initSocket();
    int dnsResolve();
    int makeNonBlocking();
};

#endif // SOCKET_HPP
