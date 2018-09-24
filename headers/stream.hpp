#ifndef STREAM_HPP
#define STREAM_HPP

#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

class Stream
{
public:
    Stream();
    Stream(int fd);
    ~Stream();
    void addDescToEpoll(int desc);          // ????????????????
    std::string getline();

    int getDesc() const;
    bool eof() const;

    void setDesc(int desk);
private:
    int descriptor;
    static const size_t BUFF_SIZE = 1024;

    std::string lineBuff;
    bool eofFlag;
};

#endif // STREAM_HPP
