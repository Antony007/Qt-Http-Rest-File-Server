#include "baselogger.h"
#include <QDebug>

using namespace D;

BaseLogger::BaseLogger()
{

}

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
