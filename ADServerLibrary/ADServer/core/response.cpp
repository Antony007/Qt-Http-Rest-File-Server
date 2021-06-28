#include "response.h"

using namespace ADServer;

Response::Response(QHttpResponse *res)
    : m_res(res)
{

}

void Response::setHeader(const QByteArray &field, const QByteArray &value)
{
    m_res->addHeader(field,value);
}

void Response::setStatus(Response::ResponseStatusCode code)
{
    m_res->setStatusCode(static_cast<qhttp::TStatusCode>(code));
}

void Response::finish(QByteArray data = QByteArray())
{
    m_res->end(data);
}
