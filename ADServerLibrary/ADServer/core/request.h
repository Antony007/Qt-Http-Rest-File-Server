#ifndef REQUEST_H
#define REQUEST_H

#include "qhttpserverrequest.hpp"

namespace ADServer {

using namespace qhttp::server;

class Request
{
public:
    Request(QHttpRequest* req);

public:
    const QUrl &url() const;
    void collectData(int atMost = -1);
    QByteArray getPostData();
    QHttpRequest *getRawRequest();
    QString getMethod();

private:
    QHttpRequest* m_req;
};

} // namespace ADServer

#endif // REQUEST_H
