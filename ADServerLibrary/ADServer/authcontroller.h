#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include "adcontroller.h"

class ADSERVERSHARED_EXPORT authController : public ADController
{
    Q_OBJECT
public:
    REGISTER_ACTION QJsonValue getValidate(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue postAuthorize(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue postRevoke(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue postDeny(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue postRequest(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue getAll(QStringList params,QByteArray data);
};

REGISTER_CONTROLLER(authController)

#endif // AUTHCONTROLLER_H
