#include <stream.hpp>

Stream::Stream()
{
    eofFlag = false;
}

Stream::Stream(int fd)// : Stream()       // Делегирование конструктора
{
    setDesc(fd);
    eofFlag = false;
}

Stream::~Stream()
{
    close(descriptor);
}

int Stream::getDesc() const
{
    return descriptor;
}

void Stream::setDesc(int fd)
{
    if (fd < 0)
    {
        fprintf (stderr, "Cannot open file!\n");
        exit (1);
    }
    descriptor = fd;
}

bool Stream::eof() const
{
    return eofFlag;
}

std::string Stream::getline()
{
    char buff[BUFF_SIZE];
    ssize_t readed_bytes;
    std::string gettedLine;
    // Пока есть данные в файле или буфер не пуст
    sleep(1);
    while((readed_bytes = read(descriptor, &buff, BUFF_SIZE)) | !lineBuff.empty())
    {
        if(readed_bytes == -1)
        {
            std::cout << strerror(errno) << " " << errno << std::endl;
        }

        // Заполняем буфер
        for(ssize_t i = 0; i < readed_bytes; ++i)
        {
            lineBuff += buff[i];
        }

        std::cout << "Zhopa zdes!" << std::endl;
//        std::cout << "Raw string = " << lineBuff << std::endl;
//        std::cout << "Stop!" << std::endl;

        //Ищем стрoку в буфере
        size_t a = lineBuff.find('\n');
        // Если есть отдельная строка в буфере, то вернём её, а буфер обрежем
        if(a != std::string::npos)
        {
            gettedLine = lineBuff.substr(0, a);
            lineBuff = lineBuff.substr(a + 1);
            return gettedLine;
        }

        // Нужно ли вообще этот блок ниже? В файле даже в последней строке есть \n
        // Уже считали всё, что могли, обработаем последнюю строку
        if(readed_bytes == 0)
        {
            return lineBuff;
        }
    }

    // Нулевое значение - конец файла
    if(readed_bytes == 0)
    {
        eofFlag = true;
    }

    return gettedLine;
}
