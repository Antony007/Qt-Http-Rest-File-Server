#include "baseserver.h"
#include "baseconnection.h"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"
#include <QTcpSocket>

using namespace D;

void BaseServer::incomingConnection(qintptr handle)
{
    BaseConnection* conn = new BaseConnection(this);
    conn->setSocketDescriptor(handle, backendType());
    conn->tcpSocket()->setSocketOption(QAbstractSocket::KeepAliveOption,1);
    conn->setTimeOut(/*QHttpServer::timeOut()*/0);

    incomingConnection(conn);
}


void BaseServer::incomingConnection(QHttpConnection *connection)
{
    QObject::connect(connection,&QHttpConnection::newRequest,this,[=](QHttpRequest* req, QHttpResponse* res){
        auto request = std::make_shared<Request>(req);
        auto response = std::make_shared<Response>(res);
        emit newRequest(request,response);
    });
}
