#include "common.h"
#include "core/app.h"

QString Common::applicationPath()
{
    return D::App::applicationDirPath();
}
