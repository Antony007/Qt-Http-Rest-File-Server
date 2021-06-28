#ifndef BASELOGGER_H
#define BASELOGGER_H

#include <QString>

namespace ADServer {

class BaseLogger
{
public:
    virtual ~BaseLogger();

protected:
    void log(QString s);

protected:
    virtual QString id();
};

} // namespace ADServer

#endif // BASELOGGER_H
