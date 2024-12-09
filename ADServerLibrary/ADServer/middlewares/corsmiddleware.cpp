#include "corsmiddleware.h"
#include "core/response.h"
#include "core/request.h"
#include <QVector>

using namespace D;

QVector<QString> corsMiddleware::m_methods = QVector<QString>() << "POST"
                                                                << "GET"
                                                                << "PUT"
                                                                << "DELETE"
                                                                << "PATCH"
                                                                << "OPTIONS";

QVector<QString> corsMiddleware::m_headers = QVector<QString>() << "X-Requested-With"
                                                                << "Content-Type"
                                                                << "Accept"
                                                                << "Origin"
                                                                << "Authorization";
QString corsMiddleware::m_origin = "http://localhost/";

void corsMiddleware::preProcess(std::shared_ptr<Request>, std::shared_ptr<Response> response)
{
    response->setHeader("Access-Control-Allow-Origin",m_origin.toUtf8());
    response->setHeader("Access-Control-Allow-Headers",vectorToDelimited(m_headers).toUtf8());
    response->setHeader("Access-Control-Allow-Methods",vectorToDelimited(m_methods).toUtf8());

    return;
}

void corsMiddleware::addMethod(QString method)
{
    m_methods.append(method);
}

void corsMiddleware::removeMethod(QString method)
{
    m_methods.removeAll(method);
}

QVector<QString> corsMiddleware::methods()
{
    return m_methods;
}

void corsMiddleware::addHeader(QString header)
{
    m_headers.append(header);
}

void corsMiddleware::removeHeader(QString header)
{
    m_headers.removeAll(header);
}

QVector<QString> corsMiddleware::headers()
{
    return m_headers;
}

void corsMiddleware::setOrigin(QString origin)
{
    m_origin = origin;
}

QString corsMiddleware::vectorToDelimited(QVector<QString> data)
{
    QString ret;
    foreach(auto d, data)
        ret += d + ",";

    ret.chop(1);

    return ret;
}
