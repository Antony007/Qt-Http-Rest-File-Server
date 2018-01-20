#include "authcontroller.h"

QJsonValue authController::getValidate(QStringList params, QByteArray data)
{
    Q_UNUSED(params)
    Q_UNUSED(data)

    QJsonObject retObject;

    if(session())
    {
        session()->SetValid(true);
        retObject.insert("session",session()->SessionID());
    }
    else
        retObject.insert("session","");

    return QJsonValue(retObject);
}

QJsonValue authController::postAuthorize(QStringList params, QByteArray data)
{
    Q_UNUSED(params)

#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    QJsonDocument requestDoc = QJsonDocument::fromJson(data);

    if(!requestDoc.isObject())
    {
        setResponse(false,"Invalid Request");
        return QJsonValue();
    }

    QJsonObject requestObj = requestDoc.object();

    QString AuthID = requestObj.value("authid").toString();

    if(!Authorizer()->GrantAccess(AuthID))
    {
        setResponse(false,"Unable to grant permission");
        return QJsonValue();
    }

    setResponse(true,"Permission Granted");

    return QJsonValue();
}

QJsonValue authController::postRevoke(QStringList params, QByteArray data)
{
    Q_UNUSED(params)

#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    QJsonDocument requestDoc = QJsonDocument::fromJson(data);

    if(!requestDoc.isObject())
    {
        setResponse(false,"Invalid Request");
        return QJsonValue();
    }

    QJsonObject requestObj = requestDoc.object();

    QString AuthID = requestObj.value("authid").toString();

    if(!Authorizer()->RevokeAccess(AuthID))
    {
        setResponse(false,"Unable to revoke permission");
        return QJsonValue();
    }

    setResponse(true,"Permission Revoked");

    return QJsonValue();
}

QJsonValue authController::postDeny(QStringList params, QByteArray data)
{
    Q_UNUSED(params)

#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    QJsonDocument requestDoc = QJsonDocument::fromJson(data);

    if(!requestDoc.isObject())
    {
        setResponse(false,"Invalid Request");
        return QJsonValue();
    }

    QJsonObject requestObj = requestDoc.object();

    QString AuthID = requestObj.value("authid").toString();

    if(!Authorizer()->DenyAccess(AuthID))
    {
        setResponse(false,"Unable to deny permission");
        return QJsonValue();
    }

    setResponse(true,"Permission Denied");

    return QJsonValue();
}

QJsonValue authController::postRequest(QStringList params, QByteArray data)
{
    Q_UNUSED(params)

    QJsonDocument requestDoc = QJsonDocument::fromJson(data);

    if(!requestDoc.isObject())
    {
        setResponse(false,"Invalid Request");
        return QJsonValue();
    }

    QJsonObject requestObj = requestDoc.object();
    QJsonValue tokenValue = requestObj.value("token");
    QJsonObject tokenObj = tokenValue.toObject();

    QString authID = tokenObj.value("sysid").toString();
    QString os = tokenObj.value("os").toString();
    QString vendor = tokenObj.value("vendor").toString();
    QString info = tokenObj.value("info").toString();

    QString email = requestObj.value("email").toString();
    QString description = requestObj.value("description").toString();

    if(!Authorizer()->RequestAccess(authID,email,os,vendor,info,description))
    {
        setResponse(false,"Unable to place request");
        return QJsonValue();
    }

    setResponse(true,"Request Successfull");

    return QJsonValue();
}

QJsonValue authController::getAll(QStringList params, QByteArray data)
{
    Q_UNUSED(data)
    Q_UNUSED(params)

#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    QJsonValue retValue;

    if(!Authorizer()->GetRequests(retValue))
    {
        setResponse(false,"Server Error");
        return QJsonValue();
    }

    return retValue;
}
