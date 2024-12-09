#include "webcontroller.h"
#include "common.h"
#include <QMimeDatabase>
#include <QDebug>

using namespace D;

bool webController::routeToIndex = false;
QString webController::webRoot = "www";

void webController::get()
{
    auto params = getParameters();

    auto path = webRoot;
    auto defaultPath = webRoot + QDir::separator() + QString("index.html");

    if(params.count() > 0)
    {
        foreach(auto param, params)
        {
            path += QDir::separator() + param;
        }
    }
    else
        path = defaultPath;

    qDebug() << path;

    if(path.endsWith(".html") && routeToIndex)
        path = defaultPath;

    qDebug() << path;

    sendFile(path);
}

void webController::setWebRoot(QString rootPath)
{
    webRoot = rootPath;
}

void webController::setRouteToIndex(bool route)
{
    routeToIndex = route;
}
