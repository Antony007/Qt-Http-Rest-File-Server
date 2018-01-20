#ifndef DEFS_H
#define DEFS_H

#include "qhttpserver.hpp"
#include "qhttpserverconnection.hpp"
#include "qhttpserverrequest.hpp"
#include "qhttpserverresponse.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

#include <authengine.h>
#include <QDate>

#include "adntaskmanager.h"
#include "export.h"

#define FREE_MEMORY(x) if(x != NULL){ delete x; x = NULL;}

const QString KDM_AUTH_DATABASE = QDir::homePath() + "/AuthDB";

const int FACTOR_BYTE2MB = 1048576; //Factor to convert Bytes to MegaBytes

const QString TEMP_STORAGE_PATH = "/tmp/AdnServeStore/";

ADNHTTPSERVERSHARED_EXPORT AuthEngine*  Authorizer();
ADNHTTPSERVERSHARED_EXPORT void  DestroyAuthorizer();
ADNHTTPSERVERSHARED_EXPORT ADN::ADNTaskManager* TaskManager();
ADNHTTPSERVERSHARED_EXPORT void DestroyTaskManager();
ADNHTTPSERVERSHARED_EXPORT QString method(QString methodString);
ADNHTTPSERVERSHARED_EXPORT QString getFileUrl(QString filePath);

#endif // DEFS_H
