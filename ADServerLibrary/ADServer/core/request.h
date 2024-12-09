#ifndef REQUEST_H
#define REQUEST_H

class QUrl;
class QByteArray;
class QString;

namespace qhttp {
namespace server {
class QHttpRequest;
}
}

namespace D {

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

} // namespace D

#endif // REQUEST_H
