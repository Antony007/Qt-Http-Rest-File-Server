#include "authengine.h"
#include <QUuid>
#include <QFile>
#include <QVariant>
#include <QDebug>
#include "adserver.h"
#include "session.h"

AuthEngine::AuthEngine()
{
    m_identifier = QUuid::createUuid().toString().left(10);
}

AuthEngine::~AuthEngine()
{
    if(m_database.isOpen())m_database.close();
}

bool AuthEngine::RegisterDatabase(QString Database)
{
    m_Error.clear();

    m_database = QSqlDatabase::addDatabase("QSQLITE",m_identifier);
    m_database.setDatabaseName(Database);
    if(!m_database.open())
    {
        m_Error = "Unable to connect to database";
        qCritical() << m_Error;
        qCritical() << "Database error";
    }
    else
    {
        qDebug() << "Database registered";
    }

    if(Init() == false)
    {
        m_Error = "Improper Database";
        qCritical() << m_Error;
        return false;
    }

    return true;
}

int AuthEngine::Validate(QString ID)
{
    int ret = -1;
    QSqlQuery query(m_database);
    query.prepare("SELECT allow FROM auth WHERE authid = (:authid)");
    query.bindValue(":authid",ID);

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return ret;
    }

    if(query.next())
    {
        int allow = query.value(0).toInt();

        if(allow == 1)
            return 0;
        else if(allow == 2)
            return 2;
        else
            return 1;
    }

    return ret;
}

bool AuthEngine::RequestAccess(QString ID, QString email,QString os,QString vendor, QString info, QString description)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO auth (email,authid,os,vendor,info,allow,description) VALUES (:email,:authid,:os,:vendor,:info,:allow,:description)");
    query.bindValue(":email",email);
    query.bindValue(":authid",ID);
    query.bindValue(":os",os);
    query.bindValue(":info",info);
    query.bindValue(":vendor",vendor);
    query.bindValue(":allow",0);
    query.bindValue(":description",description);

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    return true;
}

bool AuthEngine::GrantAccess(QString authID)
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE auth SET allow=:allow WHERE authid=:authid");
    query.bindValue(":authid",authID);
    query.bindValue(":allow",1);

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    return true;
}

bool AuthEngine::DenyAccess(QString authID)
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE auth SET allow=:allow WHERE authid=:authid");
    query.bindValue(":authid",authID);
    query.bindValue(":allow",2);

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    return true;
}

bool AuthEngine::RevokeAccess(QString authID)
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE auth SET allow=:allow WHERE authid=:authid");
    query.bindValue(":authid",authID);
    query.bindValue(":allow",0);

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    return true;
}

Session *AuthEngine::RequestSession(qhttp::server::QHttpRequest *req)
{
    QString sessionID = "";

    sessionID = GetSessionID(req);

    if(sessions.contains(sessionID))
    {
        Session* session = sessions.value(sessionID);
        session->ResetTimeout();
        return session;
    }
    else
        return NULL;
}

Session *AuthEngine::CreateSession(QString authID)
{
    Session* session = new Session(authID);
    sessions.insert(session->SessionID(),session);

    QSqlQuery query(m_database);
    query.prepare("UPDATE auth SET last_session = DATETIME(CURRENT_TIMESTAMP,'LOCALTIME') WHERE authid = :authid");
    query.bindValue(":authid",authID);
    if(!query.exec())
    {
        qDebug() << query.lastError().text();
    }

    return session;
}

int  AuthEngine::ValidateRequest(qhttp::server::QHttpRequest *req)
{
    QString authID = "";

    authID = GetAuthID(req);

    if(authID.isEmpty())
        return  -1;

    return Validate(authID);
}

QString AuthEngine::GetAuthID(qhttp::server::QHttpRequest *req)
{
    QString authid;
    authid.clear();

    if(req->headers().has("x-adn-authid"))
        authid = req->headers().value("x-adn-authid");

    return authid;
}

QString AuthEngine::GetSessionID(qhttp::server::QHttpRequest *req)
{
    QString sessionid;
    sessionid.clear();

    if(req->headers().has("x-adn-sessionid"))
        sessionid = req->headers().value("x-adn-sessionid");

    return sessionid;
}

void AuthEngine::DumpHeaders(qhttp::server::QHttpRequest *req)
{
    const auto& h = req->headers();
    h.forEach([](auto iter) {
        qDebug(" %s : %s",
               iter.key().constData(),
               iter.value().constData()
               );
    });
}

bool AuthEngine::ValidateSession(Session *session)
{
    if(!session)
    {
        return false;
    }

    if(!session->Valid())
    {
        return false;
    }

    return true;
}

bool AuthEngine::GetRequests(QJsonValue &json)
{
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM auth");
    QJsonArray requestArray;

    if(!query.exec())
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    while(query.next())
    {
        QJsonObject requestObj;
        requestObj.insert("email",query.value("email").toString());
        requestObj.insert("authid",query.value("authid").toString());
        requestObj.insert("os",query.value("os").toString());
        requestObj.insert("vendor",query.value("vendor").toString());
        requestObj.insert("info",query.value("info").toString());
        requestObj.insert("description",query.value("description").toString());

        QString last_session = query.value("last_session").toString();
        QString last_session_text = "NA";

        if(!last_session.isEmpty())
        {
            QDateTime sessionTime = QDateTime::fromString(last_session,"yyyy-MM-dd hh:mm:ss");
            int days = sessionTime.daysTo(QDateTime::currentDateTime());
            last_session_text = QString::number(days) + " days ago";
        }

        requestObj.insert("last_session",last_session_text);

        int allow = query.value("allow").toInt();
        QString status;

        if(allow == 1)
            status = "Allowed";
        else if (allow == 0)
            status = "Awaiting Permission";
        else
            status = "Denied";

        requestObj.insert("action",allow);
        requestObj.insert("status",status);

        requestArray.append(requestObj);
    }

    json = QJsonValue(requestArray);

    return true;
}

bool AuthEngine::Init()
{
    QSqlQuery query(m_database);

    if(!query.exec("CREATE TABLE IF NOT EXISTS auth(id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT, authid TEXT, os TEXT, vendor TEXT, info TEXT, allow INTEGER, description TEXT, last_session TIME)"))
    {
        qCritical() << query.lastError().text();
        qCritical() << "Database error";
        return false;
    }

    return true;
}
