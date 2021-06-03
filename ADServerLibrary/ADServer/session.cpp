#include "session.h"
#include <QUuid>
#include <QVariant>

Session::Session(QString authID) : QObject(nullptr)
{
    m_sessionTimer = new QTimer();
    m_sessionTimer->setInterval(60000);
    connect(m_sessionTimer, &QTimer::timeout, this, [=](){
        m_minutes += 1;
    });

    m_authID = authID;
    m_valid = false;
}

Session::~Session()
{
    FREE_MEMORY(m_sessionTimer);
}

bool Session::LoggedIn()
{
    return m_loggedIn;
}

bool Session::Valid()
{
    return m_valid;
}

QString Session::AuthID()
{
    return m_authID;
}

QString Session::SessionID()
{
    if(m_sessionID.isEmpty())
    {
        m_sessionID = QUuid::createUuid().toString();
    }
    return m_sessionID;
}

void Session::setLoggedIn(bool log)
{
    m_loggedIn = log;
}

void Session::SetSessionVariable(QString key, QVariant data)
{
    m_vars[key] = data;
}

bool Session::IsSetSessionVariable(QString key)
{
    return m_vars.contains(key);
}

void Session::UnSetSessionVariable(QString key)
{
    m_vars.remove(key);
}

QVariant Session::GetSessionVariable(QString key)
{
    if(m_vars.contains(key))
    {
        return m_vars[key];
    }
    else
        return QVariant();
}

void Session::ResetTimeout()
{
    m_minutes = 0;
}

void Session::SetValid(bool valid)
{
    m_valid = valid;
}
