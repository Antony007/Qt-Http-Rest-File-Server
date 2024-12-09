#ifndef SOCKET_H
#define SOCKET_H


namespace D {

class Socket
{
public:
    explicit Socket();
    virtual ~Socket();

public:
    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int write(void* buffer) = 0;
    virtual int read(void* buffer) = 0;
    virtual bool isOpen() = 0;
};

} // namespace D

#endif // SOCKET_H
