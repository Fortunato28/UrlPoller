#include <iostream>
#include <stream.hpp>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include "socket.hpp"
#include <task.hpp>

/*
void stdin_epoll()
{
    // Здесь и ниже будет опрос stdin через epoll

    int epfd = epoll_create(1);
    if(epfd == -1)
    {
        perror("epoll_create is bad");
        exit(EXIT_FAILURE);
    }

    static struct epoll_event ev;

    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1)
    {
        perror("epoll_ctl connSock is bad");
        exit(EXIT_FAILURE);
    }

    Stream stdinStream(STDIN_FILENO);
    while(true)
    {
        memset(&ev, 0, sizeof(ev));
        int nfds = epoll_wait(epfd, &ev, 1, 3000);
        if(nfds == -1)
        {
            perror("epoll_wait is bad");
            exit(EXIT_FAILURE);
        }

        std::string readedString;
         // Второе условие - есть ли что считать из стандартного ввода
         // (там битовая маска, при пайпе в неё пишется ещё и EPOLLHUP)
        if((ev.data.fd == STDIN_FILENO) && (ev.events && EPOLLIN))
        {
            // Чтение строки из потока
            readedString = stdinStream.getline();

            if(stdinStream.eof())
                break;

            // TO DO: add in taskQueue
            std::cout << "Readed string = " << readedString << std::endl;
        }
    }

    close(STDIN_FILENO); // ?????????????????????

    return;

}

int runTask(Socket &sock)
{
    // Epoll подготовка
    int epfd = epoll_create(1); // Аргумент должен быть просто больше нуля
    if(epfd == -1)
    {
        perror("epoll_create is bad");
        exit(EXIT_FAILURE);
    }

    static struct epoll_event ev, events[20];

    ev.events = EPOLLOUT;
    ev.data.fd = sock.getSock();
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, sock.getSock(), &ev) == -1)
    {
        perror("epoll_ctl connSock is bad");
        close(epfd);
        exit(EXIT_FAILURE);
    }

    int nfds = epoll_wait(epfd, events, 1, 5000);
    if(nfds == -1)
    {
        perror("epoll_wait is bad");
        close(epfd);
        exit(EXIT_FAILURE);
    }

    if((nfds == 1) && (events[0].data.fd == sock.getSock()))
    {
        sock.sendFullMessage(httpRequest);
        std::cout << "Message sended" << std::endl;
    }

    return 0;
}
*/

int main()
{
//    Stream myTestStream(open("testInput.txt", O_RDONLY | O_NONBLOCK));
//    Stream myTestStream(0);
    std::string output;

    std::cout << "Enter string:" << std::endl;

//    stdin_epoll();

//    Socket sock("matematikam.ru");
//    runTask(sock);

    std::string url = "matematikam.ru";
    Task task1(url);
    task1.run();

    return 0;
}
