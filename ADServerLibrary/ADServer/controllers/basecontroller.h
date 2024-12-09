#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

#include "export.h"
#include <QObject>
#include <QVector>
#include <QMimeDatabase>
#include "common.h"
#include "core/request.h"
#include "core/response.h"
#include "core/baseinvokable.h"
#include "core/baselogger.h"

#define API Q_INVOKABLE

namespace D {

using QueryParameters = QHash<QString,QString>;
using UrlParameters = QVector<QString>;

class ADSERVERSHARED_EXPORT BaseController : public BaseInvokable, public BaseLogger
{
    Q_OBJECT

public:
    BaseController();
    ~BaseController() override;

public:
    void setRoute(QString route);
    void process(std::shared_ptr<Request> request, std::shared_ptr<Response> response) override; // BaseInvokable interface

protected:
    void setHeader(const QByteArray& header, const QByteArray& value);
    void setContentType(QString type);
    void setStatus(Response::ResponseStatusCode code);
    void sendResponse(QByteArray response);
    std::shared_ptr<Response> getResponse() const;
    QueryParameters &getQueries();
    UrlParameters &getParameters();
    QByteArray &getPostData();

    // Assist functions
    void sendJsonResponse(QJsonObject object);
    void sendJsonResponse(QJsonDocument doc);
    void sendJsonResponse(QJsonArray array);
    void sendFile(QString path);

private:
    QString simplifiedMethodString();
    QString sanitizeUrl(QString url);


private:
    QByteArray m_data;
    QByteArray m_postData;
    UrlParameters m_params;
    QueryParameters m_queryParams;
    std::shared_ptr<Request> m_request;
    std::shared_ptr<Response> m_response;
    QString m_route;
    QMimeDatabase db;

    // BaseLogger interface
protected:
    QString id() override;
};

}

#endif // BASECONTROLLER_H
