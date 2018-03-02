# Authentication Module

### How does it work

This module is used to restrict the Apis to authorized id /s.

When this module is enabled, all the requests to the ADNHttpServer is filtered through `AuthEngine`. In your controller, you can query the current `AuthEngine` using `Authorizer()`.

On first run, the library creates a SQLite Database 'AuthDB' in the home folder. The database contains a list of all the ids allowed to make request.

The client application, requiring access to the protected Apis, requests the server for permission by providing a unique ID (IMEI incase of Mobile Phones, Some Persistent ID incase of  Browser Applications). The library adds a entry for that id in the database pending for activation. The server admin then authorizes or denies access to the id. Once authorized, the id is allowed access to the protected apis. The client application has to provide the unique ID with every request. 

### How to implement the Authentication Controller
For the application to load the Authentication Module, add the following to your **main.cpp**

* Include the 'authcontroller.h'</li>
* Add 'authController' to `ACTIVATE_CONTROLLERS`</li>
* Call `DestroyAuthorizer()` after the application event loop to free memory</li>

```C++
//...
#include "authcontroller.h"
//...
int main(int argc, char *argv[])
{
    //...

    ACTIVATE_CONTROLLERS(authController,demoController);

    ADNHttpServer::ADNServer httpserver;
    httpserver.start(1992);

    int ret = a.exec();

    DestroyAuthorizer();

    //...
}
```
To create a protected Api, at the beginning of your api method, add the verification calls.

```C++
#ifdef AUTH
    if(!Authorizer()->ValidateSession(session())) // Check if 
    {
        setResponse(false,"Invalid Session");
        return QJsonValue();
    }

    if(!session()->LoggedIn())
    {
        setResponse(false,"Unauthenticated Access. Log in to continue");
        return QJsonValue();
    }

    if(session()->GetSessionVariable("custom_verification_variable").toBool() == false) // If you want to implement your own protection
    {
        setResponse(false,"UnAuthenticated Access");
        return QJsonValue();
    }
#endif
```
