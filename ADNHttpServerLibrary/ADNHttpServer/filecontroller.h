#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include "adnhttpserver.h"

using namespace ADNHttpServer;

class ADNHTTPSERVERSHARED_EXPORT fileController: public QObject
{
    Q_OBJECT

public:
    void process(QHttpRequest* req, QHttpResponse* res, QStringList params);
    void error(QHttpResponse* res, QString comment = "Not Found");
    void success(QHttpResponse *res);
    void download(QHttpResponse* res, QStringList params);
    void upload(QHttpRequest* req, QHttpResponse* res,QStringList params);

private slots:
    void onData(QByteArray data);

protected:
    void setResponse(bool valid,QString comment){m_response.valid = valid; m_response.comment = comment;}

private:
    ADNResponse m_response;
    Session* m_session;
    QString destPath;
    int splitIndex;
    QByteArray boundary;
    QFile file;
    QString filename;
    QByteArray dataSink;
    QHttpResponse* res;
};

#endif // FILECONTROLLER_H
