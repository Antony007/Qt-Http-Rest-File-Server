#include "filecontroller.h"
#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>
#include <QTcpSocket>
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

const QString VALID_KEY = "valid";
const QString VALID_COMMENT = "comment";

void fileController::process(QHttpRequest *req, QHttpResponse *res, QStringList params)
{
    if(req->method() != qhttp::EHTTP_GET &&  req->method() != qhttp::EHTTP_POST)
    {
        success(res);
        return;
    }

    if(req->method() == qhttp::EHTTP_GET )
    {
        return download(res,params);
    }
    else
    {
        return upload(req,res,params);
    }
}

void fileController::error(QHttpResponse* res, QString comment )
{
    QJsonObject ErrorObject;
    QJsonValue ErrorValue(false);
    ErrorObject.insert(VALID_KEY,ErrorValue);
    ErrorObject.insert(VALID_COMMENT,comment);
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

void fileController::success(QHttpResponse *res)
{
    QJsonObject SuccessObject;

    QJsonValue SuccessValue(true);
    SuccessObject.insert(VALID_KEY,SuccessValue);
    SuccessObject.insert(VALID_COMMENT,"");

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

void fileController::download(QHttpResponse *res, QStringList params)
{
    if(params.count() < 1)
    {
        return error(res,"Not Found");
    }

    destPath = TEMP_STORAGE_PATH;

    QString Filename = TEMP_STORAGE_PATH + params.at(0);

    for(int i =1; i < params.count(); i++)
        Filename += "/" + params.at(i);

    if(!QFile::exists(Filename))
    {
        return error(res);
    }

    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(Filename);
    qDebug() << "Mime type:" << type.name();


    QFile file(Filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        return error(res);
    }

    res->addHeader("connection", "keep-alive");
    res->addHeader("Content-Type", type.name().toUtf8());
    res->addHeader("Access-Control-Allow-Credentials", "true");
    res->addHeader("Access-Control-Allow-Origin","*");
    res->addHeader("Access-Control-Allow-Headers:","Content-Type, Authorization, X-AD-SessionID, X-AD-AuthID");
    res->addHeaderValue("content-length", QString::number(file.size()));
    res->setStatusCode(qhttp::ESTATUS_OK);

    QByteArray buffer;
    int chunksize = 1048576; // Whatever chunk size you like
    while(!(buffer = file.read(chunksize)).isEmpty()){
        res->write(buffer);
        res->connection()->tcpSocket()->flush();
    }

    res->end();
    file.close();
    return;
}

void fileController::upload(QHttpRequest *req,  QHttpResponse* res, QStringList params)
{
#ifdef AUTH
    int valid = Authorizer()->ValidateRequest(req);

    if(valid == 0)
#endif
    {
        m_session = Authorizer()->RequestSession(req);

        if(m_session == nullptr)
            m_session = Authorizer()->CreateSession(Authorizer()->GetAuthID(req));
    }
#ifdef AUTH
    if(valid == -1)
        return error(res,"");
    if(valid == 1)
        return error(res,"Authorization pending. Contact Administrator");
    if(valid == 2)
        return error(res,"Permission Denied");
#endif

    destPath = TEMP_STORAGE_PATH;

    splitIndex = 0;
    boundary.clear();
    filename.clear();

    req->onData([=](QByteArray data) {
        onData(data);
    });

    req->onEnd([=]() {
        qDebug() << "Upload Ended";

        int boundaryIndex = dataSink.indexOf(boundary);
        dataSink = dataSink.mid(0,boundaryIndex);
        dataSink.chop(2);
        file.write(dataSink);

        if(file.isOpen())
            file.close();

        if(!filename.isEmpty())
            res->setStatusCode(qhttp::ESTATUS_OK);
        else
            res->setStatusCode(qhttp::ESTATUS_NOT_FOUND);
        res->addHeader("connection", "close");
        success(res);
    });

    return;
}

void fileController::onData(QByteArray data)
{
    if(splitIndex == 0)
    {
        splitIndex = data.indexOf("\r\n");
        boundary = data.mid(0,splitIndex);
        qDebug() << boundary;
        int startIndex = 0;
        int partIndex = data.indexOf("\r\n");
        startIndex = partIndex;//Skip Boundary
        partIndex = data.indexOf("\r\n",startIndex + 1);
        QString fileDetails = data.mid(startIndex,partIndex - startIndex);

        QStringList details = fileDetails.split(';',QString::SkipEmptyParts);
        filename = "";
        for(int i = 0; i < details.count(); i++)
        {
            QString detail = details.at(i);
            detail  = detail.simplified();

            if(detail.startsWith("filename"))
            {
                QStringList list = detail.split("=",QString::SkipEmptyParts);
                if(list.count() > 1)
                {
                    filename = list.at(1);
                    filename = filename.simplified();
                    filename = filename.replace("\"","");
                    filename = destPath + filename;
                    break;
                }
            }
        }

        if(filename.isEmpty())
            return;

        file.setFileName(filename);

        startIndex = partIndex;
        partIndex = data.indexOf("\r\n",startIndex + 1);
        QString filetype = data.mid(startIndex,partIndex - startIndex);
        qDebug() << "File Type : " << filetype;

        startIndex = partIndex;
        partIndex = data.indexOf("\r\n",startIndex + 1);
        startIndex = partIndex;
        partIndex = data.indexOf("\r\n",startIndex + 1);
        data = data.mid(startIndex + 2, -1);
        dataSink = data;
    }
    else
    {

        if(filename.isEmpty())
            return;

        if(!file.isOpen())
        {
            if(!file.open(QIODevice::WriteOnly))
                return;
        }

        file.write(dataSink);

        dataSink = data;
    }
}
