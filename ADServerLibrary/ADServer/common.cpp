#include "common.h"
#include "core/app.h"

QString Common::applicationPath()
{
    return ADServer::App::applicationDirPath();
}
