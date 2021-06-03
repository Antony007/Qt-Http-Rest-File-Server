#include <QCoreApplication>
#include "adserver.h"
#include "democontroller.h"
#include "authcontroller.h"
#include "filecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    ACTIVATE_CONTROLLERS(authController,demoController);

    qRegisterMetaType<authController>("authController");
    qRegisterMetaType<demoController>("demoController");

    ADHttpServer::ADServer httpserver;
    httpserver.start(1992);

    return a.exec();
}
