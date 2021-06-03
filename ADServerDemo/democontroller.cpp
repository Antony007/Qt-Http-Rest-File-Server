#include "democontroller.h"

QJsonValue demoController::getHello(QStringList params, QByteArray data)
{
#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    Q_UNUSED(params);
    Q_UNUSED(data);

    QJsonObject retObj;
    retObj.insert("Hello","World");

    return QJsonValue(retObj);
}

QJsonValue demoController::getError(QStringList params, QByteArray data)
{
#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    Q_UNUSED(params);
    Q_UNUSED(data);

    setResponse(false,"This is a demo error");

    return QJsonValue();
}
