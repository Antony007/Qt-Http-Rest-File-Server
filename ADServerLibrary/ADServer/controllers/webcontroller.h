#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

#include "basecontroller.h"
#include "export.h"

namespace ADServer {

class ADSERVERSHARED_EXPORT webController : public BaseController
{
    Q_OBJECT
public:
    API void get();

public:
    static void setWebRoot(QString rootPath);
    static void setRouteToIndex(bool route);

private:
    static QString webRoot;
    static bool routeToIndex;
};

}

#endif // WEBCONTROLLER_H
