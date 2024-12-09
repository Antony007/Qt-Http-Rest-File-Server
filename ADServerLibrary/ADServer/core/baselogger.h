#ifndef BASELOGGER_H
#define BASELOGGER_H

#include "export.h"
#include <QString>

namespace D {

class ADSERVERSHARED_EXPORT BaseLogger
{
public:
    BaseLogger();
    virtual ~BaseLogger();
    BaseLogger(const BaseLogger &logger) = delete;
    BaseLogger& operator=(BaseLogger logger) = delete;

protected:
    void log(QString s);

protected:
    virtual QString id();
};

} // namespace D

#endif // BASELOGGER_H
