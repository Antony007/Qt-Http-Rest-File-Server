#ifndef BASECONNECTION_H
#define BASECONNECTION_H

#include "common.h"
#include "export.h"
#include "qhttpserverconnection.hpp"

namespace D {
using namespace qhttp::server;

class ADSERVERSHARED_EXPORT BaseConnection : public QHttpConnection
{
    using QHttpConnection::QHttpConnection;

public:
    BaseConnection(QObject *parent = nullptr);

protected:
    friend class BaseServer;
};

}

#endif // BASECONNECTION_H
