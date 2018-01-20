#include <QCoreApplication>
#include "adnhttpserver.h"
#include "registers.h"
#include "unixcatcher.hpp"
#include "logincontroller.h"
#include "screencontroller.h"
#include "contentcontroller.h"
#include "dashcontroller.h"
#include "playlistcontroller.h"
#include "logcontroller.h"
#include "playbackcontroller.h"
#include "usercontroller.h"
#include "authcontroller.h"
#include "reportcontroller.h"
#include "archivecontroller.h"
#include "sitecontroller.h"
#include "dcicontroller.h"
#include "timecontroller.h"
#include "datacontroller.h"
#include "producercontroller.h"
#include "deathhandler.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if defined(Q_OS_UNIX)
//    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    Debug::DeathHandler dh;
#endif

    bool success = InitApplication(a);

    sessions.clear();

#ifndef ONLINE
    success = KDMTool()->RegisterDatabase(KDM_LOCAL_DATABASE,KDM::SQLITE); //Try registering database with KDM library
#else
    success = KDMTool()->RegisterDatabase(KDM_DATABASE,KDM::MYSQL,KDM_DATABASE_HOST,KDM_DATABASE_USER,KDM_DATABASE_PASS); //Try registering database with KDM library
#endif

    if(!success)
    {
        qDebug() << "Unable to Connect to Database";
        DestroyKDMTool();
        return 1;
    }

    success = Authorizer()->RegisterDatabase(KDM_AUTH_DATABASE);

    if(!success)
    {
        qDebug() << "Unable to Connect to Auth Database";
        DestroyAuthorizer();
        return 1;
    }

    qsrand((uint)QTime::currentTime().msec());

    qDebug() << "Registering Server";

    ConnectServer();

    qDebug() << "Starting Messaging Service";

    MessagingService()->start();

    qDebug() << "Starting Versioning Service";

    VersioningService()->start();

    ACTIVATE_CONTROLLERS(loginController,screenController,contentController,dashController,playlistController,logController,playbackController,userController,authController,reportController,archiveController,siteController,dciController,timeController,dataController,producerController);

    ADNHttpServer::ADNServer httpserver;
    bool ret =  httpserver.start(1992);
    DestroyKDMTool();
    DestroyAuthorizer();
    DestroyConnectServer();
    return ret;
}
