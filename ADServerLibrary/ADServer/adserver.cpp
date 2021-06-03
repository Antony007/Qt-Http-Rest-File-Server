#include "adserver.h"
#include "adcontroller.h"
#include <QMetaType>
#include <QTcpSocket>
#include <QMimeDatabase>
#include <QMimeType>
#include <QThread>
#include "filecontroller.h"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

using namespace ADHttpServer;

const QString VALID_KEY = "valid";
const QString VALID_COMMENT = "comment";
const QString SESSION_ID = "session";

int ADServer::start(quint16 port) {
    connect(this, &QHttpServer::newConnection,this,&ADServer::onNewConnection);
    connect(this, &QHttpServer::newRequest,this,&ADServer::onNewRequest);

    bool isListening = listen(QString::number(port));

    if ( !isListening ) {
        qCritical("can not listen on %d!\n", port);
        return -1;
    }

    QDir dir(TEMP_STORAGE_PATH);
    if(!dir.exists())
        dir.mkdir(TEMP_STORAGE_PATH);

    return 0;
}

void ADServer::process(QHttpRequest* req, QHttpResponse* res)
{
    QString urlString = req->url().toDisplayString();
    ADConnection* connection = dynamic_cast<ADConnection*>(req->connection());
    Q_UNUSED(connection)

    QStringList params = urlString.split('/',QString::SkipEmptyParts);
    int paramCount = params.count();

    if(paramCount < 1)
    {
        return success(res);
    }

    QString className = params.takeAt(0) + "Controller";

    if(className.compare("fileController",Qt::CaseInsensitive) == 0)
    {
        fileController *controllerPtr = new fileController;
        controllerPtr->process(req,res,params);
        FREE_MEMORY(controllerPtr);
        return;
    }
    else
    {
        int id = QMetaType::type(className.toStdString().c_str());
        if (id != QMetaType::UnknownType)
        {
            ADController *controllerPtr = static_cast<ADController*>(QMetaType::create(id));

            if(controllerPtr)
            {
                QJsonValue retJson;
                bool success = controllerPtr->process(req,params,req->collectedData(),retJson);

                if(success)
                    reply(res,retJson,controllerPtr->response());
                else
                    methoderror(res);

                QMetaType::destroy(id, controllerPtr);
                controllerPtr = nullptr;
            }
            else
            {
                return error(res);
            }
        }
        else
        {
            return error(res);
        }
    }
}

void ADServer::error(QHttpResponse* res)
{
    QJsonObject ErrorObject;
    QJsonValue ErrorValue(false);
    ErrorObject.insert(VALID_KEY,ErrorValue);
    ErrorObject.insert(VALID_COMMENT,"Not Found");
    //    ErrorObject.insert(SESSION_ID,(dynamic_cast<ADConnection*>(res->connection())->SessionID()));

    QJsonDocument ErrorDocument(ErrorObject);
    QByteArray ErrorJson = ErrorDocument.toJson();

    res->addHeader("Connection", "keep-alive");
    res->addHeader("Content-Type", "application/json");
    res->addHeader("Access-Control-Allow-Credentials", "true");
    res->addHeader("Access-Control-Allow-Origin","*");
    res->addHeader("Access-Control-Allow-Headers:","Content-Type, Authorization, X-AD-SessionID, X-AD-AuthID");
    res->addHeaderValue("content-length", ErrorJson.size());
    res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
    res->end(ErrorJson);
}

void ADServer::methoderror(QHttpResponse *res)
{
    QJsonObject ErrorObject;
    QJsonValue ErrorValue(false);
    ErrorObject.insert(VALID_KEY,ErrorValue);
    ErrorObject.insert(VALID_COMMENT,"Not Found");
    //    ErrorObject.insert(SESSION_ID,(dynamic_cast<ADConnection*>(res->connection())->SessionID()));

    QJsonDocument ErrorDocument(ErrorObject);
    QByteArray ErrorJson = ErrorDocument.toJson();

    res->addHeader("Connection", "keep-alive");
    res->addHeader("Content-Type", "application/json");
    res->addHeader("Access-Control-Allow-Credentials", "true");
    res->addHeader("Access-Control-Allow-Origin","*");
    res->addHeader("Access-Control-Allow-Headers:","Content-Type, Authorization, X-AD-SessionID, X-AD-AuthID");
    res->addHeaderValue("content-length", ErrorJson.size());
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->end(ErrorJson);
}

void ADServer::success(QHttpResponse *res)
{
    QJsonObject SuccessObject;

    QJsonValue SuccessValue(true);
    SuccessObject.insert(VALID_KEY,SuccessValue);
    SuccessObject.insert(VALID_COMMENT,"");
    //    SuccessObject.insert(SESSION_ID,connection->SessionID());

    QJsonDocument SuccessDocument(SuccessObject);
    QByteArray SuccessJson = SuccessDocument.toJson();

    res->addHeader("connection", "keep-alive");
    res->addHeader("Content-Type", "application/json");
    res->addHeader("Access-Control-Allow-Credentials", "true");
    res->addHeader("Access-Control-Allow-Origin","*");
    res->addHeader("Access-Control-Allow-Headers:","Content-Type, Authorization, X-AD-SessionID, X-AD-AuthID");
    res->addHeaderValue("content-length", SuccessJson.size());
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->end(SuccessJson);
}

void ADServer::reply(QHttpResponse *res, QJsonValue json, ADResponse response)
{
    QJsonObject ResponseObject;
    if(!json.isNull())
        ResponseObject.insert("response",json);

    ResponseObject.insert(VALID_KEY,response.valid);
    ResponseObject.insert(VALID_COMMENT,response.comment);
    //    ResponseObject.insert(SESSION_ID,(dynamic_cast<ADConnection*>(res->connection())->SessionID()));

    QJsonDocument ResponseDocument(ResponseObject);
    QByteArray reply = ResponseDocument.toJson();
    res->addHeader("connection", "keep-alive");
    res->addHeader("Content-Type", "application/json");
    res->addHeader("Access-Control-Allow-Credentials", "true");
    res->addHeader("Access-Control-Allow-Origin","*");
    res->addHeader("Access-Control-Allow-Headers:","Content-Type, Authorization, X-AD-SessionID, X-AD-AuthID");
    res->addHeaderValue("content-length", reply.size());
    res->setStatusCode(qhttp::ESTATUS_OK);
    res->end(reply);
}

void ADServer::onNewConnection(QHttpConnection *)
{
    qDebug() << "A new connection has been come!";
}

void ADServer::onNewRequest(QHttpRequest *req, QHttpResponse *res)
{
    QString urlString = req->url().toDisplayString();
    ADConnection* connection = dynamic_cast<ADConnection*>(req->connection());
    Q_UNUSED(connection)

    QStringList params = urlString.split('/',QString::SkipEmptyParts);
    int paramCount = params.count();

    if(paramCount < 1)
    {
        return success(res);
    }

    QString className = params.takeAt(0) + "Controller";

    if(className.compare("fileController",Qt::CaseInsensitive) == 0)
    {
        fileController *controllerPtr = new fileController;
        return controllerPtr->process(req,res,params);;
    }
    else
    {
        req->collectData();
        req->onEnd([this, req, res](){
            process(req, res);
        });
    }
}

void ADHttpServer::ADServer::incomingConnection(qintptr handle)
{
    ADConnection* conn = new ADConnection(this);
    conn->setSocketDescriptor(handle, backendType());
    conn->tcpSocket()->setSocketOption(QAbstractSocket::KeepAliveOption,1);
    conn->setTimeOut(/*QHttpServer::timeOut()*/0);

    emit newConnection(conn);
    QHttpServer::incomingConnection(conn);
}
