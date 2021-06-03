#include "defs.h"

static AuthEngine*  auth = NULL;
static AD::ADTaskManager* taskManager = NULL;


QString method(QString methodString)
{
    QString ret = "";
    QStringList tmp = methodString.split('_');

    if(tmp.count() == 1)
    {
        ret = tmp.at(0);
        ret = ret.toLower();
    }

    if(tmp.count() > 1)
    {
        ret = tmp.at(1);
        ret = ret.toLower();
    }

    return ret;
}

QString getFileUrl(QString filePath)
{
    return "http://192.168.0.8:1992/file/" + filePath;
}

AuthEngine *Authorizer()
{
    if(auth == NULL)
    {
        auth = new AuthEngine;
    }

    return auth;
}

void DestroyAuthorizer()
{
    FREE_MEMORY(auth);
}

AD::ADTaskManager *TaskManager()
{
    if(taskManager == NULL)
    {
        taskManager = new AD::ADTaskManager;
    }

    return taskManager;
}

void DestroyTaskManager()
{
    FREE_MEMORY(taskManager);
}
