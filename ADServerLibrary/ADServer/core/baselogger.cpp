#include "baselogger.h"
#include <QDebug>

using namespace ADServer;

BaseLogger::~BaseLogger()
{

}

void BaseLogger::log(QString s)
{
    qDebug() << "[" << id() << "] " << s;
}

QString BaseLogger::id()
{
    return "LOG";
}
