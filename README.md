# Qt Http / Rest / File Server

A Http, REST and File server written using Qt C++. 

This project also uses the library/code from the below projects:

- [QHttp](https://github.com/azadkuh/qhttp)
- [DeathHandler](https://github.com/vmarkovtsev/DeathHandler)

This project tries to follow the MVC (Model-View-Controller) pattern used by many webservices frameworks

### Enviornment

This project was built and tested with Qt v5.5 and Ubuntu. This project requires c++14

### Features
- Built-in Authentication.*(Incase you want to restrict your rest api to users approved by you only.)*
- Session Management. *(Set and use session variable like PHP)*
- MVC Approach *(Create a controller class and add methods for actions)*
- Support for large file uploads. *(Support uploading files >500MB to **remaining space in your harddisk** :wink:)*
- Support for download of large files
- Crash info using [DeathHandler](https://github.com/vmarkovtsev/DeathHandler)
- Built on top of [QHttp](https://github.com/azadkuh/qhttp). *(A well tested and live project)*

### Coming up
- A TaskManager for managing time consuming tasks which other wise leads to time-out on client side. *(Can be used to show progress bar on the client end i.e. Browsers,..etc)*
- A Helper class for server-side processing of [JQuery Datatables](https://datatables.net/).

### How to
Lets suppose you want to handle a request: `GET localhost:1992/demo/Hello`
- Link to the ADNServer Library.
- Create a class named demoController derived from ADNController as shown below.
```C++
#include "adncontroller.h"

class demoController : public ADNController
{
};

REGISTER_CONTROLLER(demoController)
```
- Add a GET Method for Hello
```C++
#include "adncontroller.h"

class demoController : public ADNController
{
    Q_OBJECT
public:
    REGISTER_ACTION QJsonValue getHello(QStringList params,QByteArray data);
};

REGISTER_CONTROLLER(demoController)
```
```C++
#include "democontroller.h"

QJsonValue demoController::getHello(QStringList params, QByteArray data)
{
#ifdef AUTH
    if(!Authorizer()->ValidateSession(session()))
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }
#endif

    Q_UNUSED(params);
    Q_UNUSED(data);

    QJsonObject retObj;
    retObj.insert("Hello","World");

    return QJsonValue(retObj);
}
```
- Add the demoController class to `ACTIVATE_CONTROLLER` in the main().
```C++
ACTIVATE_CONTROLLERS(authController,demoController);
```
- Start the server.
```C++
#include <QCoreApplication>
#include "adnhttpserver.h"
#include "democontroller.h"
#include "authcontroller.h"
#include "filecontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ACTIVATE_CONTROLLERS(authController,demoController);

    ADNHttpServer::ADNServer httpserver;
    httpserver.start(1992);

    return a.exec();
}
```
- Open your browser and go to localhost:1992/demo/Hello
### Copyleft
###### Distributed under the GPLv3 license. Copyright (c) 2018, Antony Nadar.
