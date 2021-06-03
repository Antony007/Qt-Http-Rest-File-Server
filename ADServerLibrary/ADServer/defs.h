#ifndef DEFS_H
#define DEFS_H

#include "qhttpfwd.hpp"
#include "export.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>

#include <authengine.h>
#include <QDate>

#include "adtaskmanager.h"

#define FREE_MEMORY(x) if(x != NULL){ delete x; x = NULL;}

const QString KDM_AUTH_DATABASE = QDir::homePath() + "/AuthDB";

const int FACTOR_BYTE2MB = 1048576; //Factor to convert Bytes to MegaBytes

const QString TEMP_STORAGE_PATH = "/tmp/AdServeStore/";

ADSERVERSHARED_EXPORT AuthEngine*  Authorizer();
ADSERVERSHARED_EXPORT void  DestroyAuthorizer();
ADSERVERSHARED_EXPORT AD::ADTaskManager* TaskManager();
ADSERVERSHARED_EXPORT void DestroyTaskManager();
ADSERVERSHARED_EXPORT QString method(QString methodString);
ADSERVERSHARED_EXPORT QString getFileUrl(QString filePath);

#endif // DEFS_H
