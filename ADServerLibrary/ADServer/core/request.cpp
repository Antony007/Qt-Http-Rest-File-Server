#include "request.h"
#include "qhttpserverrequest.hpp"

using namespace D;

Request::Request(QHttpRequest *req)
    : m_req(req)
{

}

const QUrl &Request::url() const
{
    return m_req->url();
}

void Request::collectData(int atMost)
{
    return m_req->collectData(atMost);
}

QByteArray Request::getPostData()
{
    return m_req->collectedData();
}

QHttpRequest *Request::getRawRequest()
{
    return m_req;
}

QString Request::getMethod()
{
    QString ret = "";
    QString methodString = m_req->methodString();
    QStringList tmp = methodString.split('_');

    if(tmp.count() == 1)
    {
        ret = tmp.at(0);
        ret = ret.toLower();
    }

    if(tmp.count() > 1)
    {
        ret = tmp.at(1);
        ret = ret.toLower();
    }

    return ret;
}
