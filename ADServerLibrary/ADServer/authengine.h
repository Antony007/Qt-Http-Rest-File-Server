#ifndef AUTHENGINE_H
#define AUTHENGINE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include  "qhttpfwd.hpp"

class Session;

static QHash<QString,Session*> sessions;

class AuthEngine
{
public:
    AuthEngine();
    ~AuthEngine();

public:
    bool RegisterDatabase(QString Database);
    int Validate(QString ID);
    bool RequestAccess(QString ID, QString email, QString os, QString vendor, QString info, QString description);
    bool GrantAccess(QString authID);
    bool DenyAccess(QString authID);
    bool RevokeAccess(QString authID);
    Session* RequestSession(qhttp::server::QHttpRequest* req);
    Session* CreateSession(QString authID);
    int ValidateRequest(qhttp::server::QHttpRequest* req);
    QString GetAuthID(qhttp::server::QHttpRequest* req);
    QString GetSessionID(qhttp::server::QHttpRequest* req);
    void DumpHeaders(qhttp::server::QHttpRequest* req);
    bool ValidateSession(Session* session);
    bool GetRequests(QJsonValue& json);

private:
    bool Init();

private:
    QSqlDatabase m_database;
    QString m_identifier;
    QString m_Error;
};

#endif // AUTHENGINE_H
