#ifndef DEMOCONTROLLER_H
#define DEMOCONTROLLER_H

#include "controllers/basecontroller.h"

using namespace ADServer;

class demoController : public BaseController
{
    Q_OBJECT
public:
    API void get();
};

#endif // DEMOCONTROLLER_H
