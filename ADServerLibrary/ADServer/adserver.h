#ifndef KDMSERVER_H
#define KDMSERVER_H

#include "defs.h"
#include "qhttpserver.hpp"
#include "qhttpserverconnection.hpp"

namespace ADHttpServer {
using namespace qhttp::server;

class ADSERVERSHARED_EXPORT ADResponse
{
public:
    bool valid;
    QString comment;
};

struct ADSERVERSHARED_EXPORT ADServer : public QHttpServer
{
    using QHttpServer::QHttpServer;

    int start(quint16 port);
    void process(QHttpRequest* req, QHttpResponse* res);
    void error(QHttpResponse* res);
    void methoderror(QHttpResponse* res); //For CORS
    void success(QHttpResponse *res);
    void reply(QHttpResponse *res, QJsonValue json,ADResponse response);

private slots:
    void onNewConnection(QHttpConnection*);
    void onNewRequest(QHttpRequest *req, QHttpResponse *res);

    // QHttpServer interface
protected:
    virtual void incomingConnection(qintptr handle);
}; // struct server
///////////////////////////////////////////////////////////////////////////////
struct ADSERVERSHARED_EXPORT ADConnection : public QHttpConnection
{
    using QHttpConnection::QHttpConnection;

public:
    ADConnection(QObject *parent = nullptr);

protected:
    friend struct ADServer;
};
} // namespace server
#endif // KDMSERVER_H
