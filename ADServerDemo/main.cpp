#include <QCoreApplication>
#include "core/app.h"
#include "controllers/webcontroller.h"
#include "democontroller.h"

int main(int argc, char *argv[])
{
    ADServer::App app(argc, argv);

    webController::setWebRoot(Common::applicationPath() + QDir::separator() + "www");

    app.addRoute<webController>("/");
    app.addRoute<demoController>("/demo");

    int ret = app.start(1992);

    return ret;
}
