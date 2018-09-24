#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include "socket.hpp"
#include <stream.hpp>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>

class Task
{
public:
    Task(std::string &url);
    void run();
private:
    void checkUrl();                    // Базовая проверка корректности url
    std::string siteName;
    Socket sock = Socket(siteName);
    Stream sockStream;

    std::string httpRequest;
    std::string httpResponse;
};

#endif // TASK_HPP
