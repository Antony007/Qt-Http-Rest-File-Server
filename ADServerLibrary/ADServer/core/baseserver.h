#ifndef BASESERVER_H
#define BASESERVER_H

#include "qhttpserver.hpp"
#include "request.h"
#include "response.h"

namespace ADServer {
using namespace qhttp::server;

class BaseServer : public QHttpServer
{
    Q_OBJECT
signals:
    void newRequest(std::shared_ptr<Request> req, std::shared_ptr<Response> res);

    // QHttpServer interface
protected:
    void incomingConnection(qintptr handle) override;

    // QHttpServer interface
protected:
    void incomingConnection(QHttpConnection *connection) override;
};

} // namespace ADServer

#endif // BASESERVER_H
