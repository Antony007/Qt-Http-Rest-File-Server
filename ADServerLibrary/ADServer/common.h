#ifndef DEFS_H
#define DEFS_H

#include "export.h"
#include <QString>
#include <QDir>

#define FREE_MEMORY(x) if(x != NULL){ delete x; x = NULL;}
#define FACTOR_BYTE2MB 1048576; //Factor to convert Bytes to MegaBytes

struct ADSERVERSHARED_EXPORT Common {
static QString applicationPath();
};

#endif // DEFS_H
