#ifndef KDMSERVER_H
#define KDMSERVER_H

#include "export.h"

#include "defs.h"
#include "qhttpfwd.hpp"

namespace ADNHttpServer {
using namespace qhttp::server;
///////////////////////////////////////////////////////////////////////////////
/// \brief The ADNServer struct

class ADNHTTPSERVERSHARED_EXPORT ADNResponse
{
public:
    bool valid;
    QString comment;
};

struct ADNHTTPSERVERSHARED_EXPORT ADNServer : public QHttpServer
{
    using QHttpServer::QHttpServer;

    int start(quint16 port);
    void process(QHttpRequest* req, QHttpResponse* res);
    void error(QHttpResponse* res);
    void methoderror(QHttpResponse* res); //For CORS
    void success(QHttpResponse *res);
    void reply(QHttpResponse *res, QJsonValue json,ADNResponse response);

private slots:
    void onNewConnection(QHttpConnection*);
    void onNewRequest(QHttpRequest *req, QHttpResponse *res);

    // QHttpServer interface
protected:
    virtual void incomingConnection(qintptr handle);
}; // struct server
///////////////////////////////////////////////////////////////////////////////
struct ADNHTTPSERVERSHARED_EXPORT ADNConnection : public QHttpConnection
{
    using QHttpConnection::QHttpConnection;

public:
    ADNConnection(QObject *parent = 0);

protected:
    friend class ADNServer;
};
} // namespace server
#endif // KDMSERVER_H
