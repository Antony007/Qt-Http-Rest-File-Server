#ifndef PORT_H
#define PORT_H

#include "socket.h"

namespace D {

class Port : public Socket
{
public:
    Port(int port);

private:
    int m_port;
};

} // namespace D

#endif // PORT_H
