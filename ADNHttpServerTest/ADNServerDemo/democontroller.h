#ifndef DEMOCONTROLLER_H
#define DEMOCONTROLLER_H

#include "adncontroller.h"

class demoController : public ADNController
{
    Q_OBJECT
public:
    REGISTER_ACTION QJsonValue getHello(QStringList params,QByteArray data);
    REGISTER_ACTION QJsonValue getError(QStringList params,QByteArray data);
};

REGISTER_CONTROLLER(demoController)

#endif // DEMOCONTROLLER_H
