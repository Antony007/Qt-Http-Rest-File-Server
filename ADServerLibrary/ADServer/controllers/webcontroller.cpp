#include "webcontroller.h"
#include "common.h"
#include <QMimeDatabase>

using namespace ADServer;

bool webController::routeToIndex = false;
QString webController::webRoot = Common::applicationPath() + QDir::separator() + "www";

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

    if(path.endsWith(".html") && routeToIndex)
        path = defaultPath;

    QFile f(path);
    if(!f.open(QFile::ReadOnly))
    {
        setStatus(Response::STATUS_NOT_FOUND);
        return;
    }

    auto data = f.readAll();
    f.close();

    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(path);

    setContentType(type.name());
    sendResponse(data);
}

void webController::setWebRoot(QString rootPath)
{
    webRoot = rootPath;
}

void webController::setRouteToIndex(bool route)
{
    routeToIndex = route;
}
