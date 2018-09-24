#include <task.hpp>

Task::Task(std::string &url) : siteName(url)
{
    checkUrl();

    sockStream.setDesc(sock.getSock());

    httpRequest = "HEAD HTTP/1.1\r\nHost: www.matematikam.ru \r\nConnection: close\r\n\r\n";

    return;
}

void Task::run()
{
    // Здесь и ниже будет опрос stdin через epoll

    int epfd = epoll_create(1);
    if(epfd == -1)
    {
        perror("epoll_create is bad");
        exit(EXIT_FAILURE);
    }

    static struct epoll_event ev;

    ev.events = EPOLLIN | EPOLLOUT;           // Готов ли сокет к отправке запроса серверу
    ev.data.fd = sock.getSock();
    if(epoll_ctl(epfd, EPOLL_CTL_ADD, sock.getSock(), &ev) == -1)
    {
        perror("epoll_ctl connSock is bad");
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        memset(&ev, 0, sizeof(ev));
        int nfds = epoll_wait(epfd, &ev, 1, 3000);
        if(nfds == -1)
        {
            perror("epoll_wait is bad");
            exit(EXIT_FAILURE);
        }

        if(ev.data.fd == sock.getSock() && ev.events && EPOLLOUT)
        {
            int sended = sock.sendFullMessage(httpRequest);
            // Отправили весь запрос полностью
            if(sended == httpRequest.length())
            {
                std::cout << "Otpravila" << std::endl;
            }
        }

        memset(&ev, 0, sizeof(ev));
        nfds = epoll_wait(epfd, &ev, 1, 3000);
        if(nfds == -1)
        {
            perror("epoll_wait is bad");
            exit(EXIT_FAILURE);
        }

        if(ev.data.fd == sock.getSock() && ev.events && EPOLLIN)
        {
            while(true)
            {
//                sleep(1);             // Почему-то этот слип решает проблему
                httpResponse = sockStream.getline();

                if(sockStream.eof())
                {
                    break;
                }
                std::cout << httpResponse << std::endl;
            }
            break;
        }
    }

    return;
}

void Task::checkUrl()
{
    // TO DO
    // Написать проверку на корректность переданой строки, т.е. url ли там вообще.
    // С помощью регулярки или конечного автомата
    return;
}
