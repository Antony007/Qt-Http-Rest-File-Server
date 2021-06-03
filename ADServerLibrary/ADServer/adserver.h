#ifndef KDMSERVER_H
#define KDMSERVER_H

#include "export.h"

#include "defs.h"

namespace ADNHttpServer {
using namespace qhttp::server;

class ADSERVERSHARED_EXPORT ADNResponse
{
public:
    bool valid;
    QString comment;
};

class ADServerPrivate;
class ADSERVERSHARED_EXPORT ADServer
{
public:
    int start(quint16 port);
    void process(QHttpRequest* req, QHttpResponse* res);
    void error(QHttpResponse* res);
    void methoderror(QHttpResponse* res); //For CORS
    void success(QHttpResponse *res);
    void reply(QHttpResponse *res, QJsonValue json,ADNResponse response);

private:
    Q_DECLARE_PRIVATE(ADServer)
    Q_DISABLE_COPY(ADServer)
    QScopedPointer<ADServerPrivate>  d_ptr;
};

struct ADSERVERSHARED_EXPORT ADNServer : public QHttpServer
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
struct ADSERVERSHARED_EXPORT ADNConnection : public QHttpConnection
{
    using QHttpConnection::QHttpConnection;

public:
    ADNConnection(QObject *parent = 0);

protected:
    friend class ADNServer;
};
} // namespace server
#endif // KDMSERVER_H
