#ifndef SESSION_H
#define SESSION_H

#include "defs.h"
#include "qhttpfwd.hpp"
#include <QTimer>
#include <QObject>

class Session : public QObject
{
    Q_OBJECT

public:
    Session(QString authID);
    ~Session();

public:
    bool LoggedIn();
    bool Valid();
    QString AuthID();
    QString SessionID();
    void setLoggedIn(bool log);
    void SetSessionVariable(QString key, QVariant data);
    bool IsSetSessionVariable(QString key);
    void UnSetSessionVariable(QString key);
    QVariant GetSessionVariable(QString key);
    void ResetTimeout();
    void SetValid(bool valid);

private:
    bool m_loggedIn;
    QString m_authID;
    QString m_sessionID;
    QMap<QString,QVariant> m_vars;
    bool m_database;
    int m_minutes;
    QTimer* m_sessionTimer;
    bool m_valid;
};

#endif // SESSION_H
