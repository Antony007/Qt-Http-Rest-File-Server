/*****************************************************************************
** <DLicenser License=GPL>
**
** adserver_p.h
**
** Created: 01-01-2019 2019 by Antony Das
**
** Copyright 2019 Antony Das. All rights reserved.
**
** Contact: http://antonydas.me/
**
** This file may be distributed under the terms of GNU Public License version
** 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
** license should have been included with this file, or the project in which
** this file belongs to. You may also find the details of GPL v3 at:
** http://www.gnu.org/licenses/gpl-3.0.txt
**
** If you have any questions regarding the use of this file, feel free to
** contact the author of this file, or the owner of the project in which
** this file belongs to.
**
**</DLicenser License=GPL>
******************************************************************************/


#ifndef ADSERVER_P_H
#define ADSERVER_P_H

#include "qhttpfwd.hpp"

class ADServerPrivate : qhttp::server::QHttpServer
{
public:
    int start(quint16 port);
    void process(qhttp::server::QHttpRequest* req, qhttp::server::QHttpResponse* res);
    void error(qhttp::server::QHttpResponse* res);
    void methoderror(qhttp::server::QHttpResponse* res); //For CORS
    void success(qhttp::server::QHttpResponse *res);
    void reply(qhttp::server::QHttpResponse *res, QJsonValue json,ADNResponse response);

private slots:
    void onNewConnection(qhttp::server::QHttpConnection*);
    void onNewRequest(qhttp::server::QHttpRequest *req, QHttpResponse *res);

    // QHttpServer interface
protected:
    virtual void incomingConnection(qintptr handle);
};

#endif // ADSERVER_P_H
