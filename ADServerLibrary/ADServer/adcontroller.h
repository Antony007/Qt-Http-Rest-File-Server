#ifndef KDMCONTROLLER_H
#define KDMCONTROLLER_H

#include "export.h"

#include "registers.h"
#include <QStringList>
#include <QByteArray>
#include <QObject>
#include "adserver.h"
#include "session.h"
#include "defs.h"
#include "qhttpserverrequest.hpp"

using namespace ADHttpServer;

class ADSERVERSHARED_EXPORT ADController : public QObject
{
    Q_OBJECT

public:
    ADController(){m_response.valid = true; m_response.comment = ""; m_session = nullptr;}
    ADController(const ADController& obj): QObject(nullptr){m_response = obj.m_response;}
    ~ADController(){}

public:
    bool process(QHttpRequest* req, QStringList params, QByteArray data,QJsonValue& ret)
    {
        if(params.count() < 1)
        {
            return false;
        }

        this->req = req;

        if(req->method() == qhttp::EHTTP_OPTIONS)
        {
            return false;
        }

#ifdef AUTH
        int valid = Authorizer()->ValidateRequest(this->req);

        if(valid == 0)
#endif
        {
            m_session = Authorizer()->RequestSession(this->req);

            if(m_session == NULL)
                m_session = Authorizer()->CreateSession(Authorizer()->GetAuthID(this->req));
        }
#ifdef AUTH
        if(valid == -1)
            setResponse(false,"");
        if(valid == 1)
            setResponse(true,"Authorization pending. Contact Administrator");
        if(valid == 2)
            setResponse(true,"Permission Denied");
#endif

        QJsonValue retjson;

        QString methodName = method(req->methodString()) + params.takeAt(0);
        bool success =  QMetaObject::invokeMethod(this,methodName.toStdString().c_str(),Qt::DirectConnection,Q_RETURN_ARG(QJsonValue, retjson),Q_ARG(QStringList, params),Q_ARG(QByteArray, data));

        if(success)
            ret = retjson;
        else
            ret = "";

        return success;
    }

    ADResponse response(){return m_response;}
    QHttpRequest* request(){return req;}
    ADConnection* connection(){return dynamic_cast<ADConnection*>(req->connection());}
    Session* session(){ return m_session; }

protected:
    void setResponse(bool valid,QString comment){m_response.valid = valid; m_response.comment = comment;}

private:
    ADResponse m_response;
    QHttpRequest* req;
    Session* m_session;
};

#endif // KDMCONTROLLER_H
