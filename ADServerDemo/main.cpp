#include <QCoreApplication>
#include "core/app.h"
#include "controllers/webcontroller.h"
#include "middlewares/corsmiddleware.h"
#include "democontroller.h"

int main(int argc, char *argv[])
{
    D::App app(argc, argv);

    webController::setWebRoot(Common::applicationPath() + QDir::separator() + "www");
    webController::setRouteToIndex(true);

    app.addMiddleware<corsMiddleware>();

    app.addRoute<webController>("/");
    app.addRoute<demoController>("/demo");

    int ret = app.start(1992);

    return ret;
}
