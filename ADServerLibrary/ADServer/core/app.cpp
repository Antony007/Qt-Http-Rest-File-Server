#include "app.h"
#include <QMetaType>
#include <QTcpSocket>
#include <QMimeDatabase>
#include <QMimeType>
#include <QThread>
#include "baseconnection.h"
#include "request.h"
#include "response.h"
#include "controllers/basecontroller.h"
#include "middlewares/basemiddleware.h"
#include "baseserver.h"
#include "qhttpserverrequest.hpp"

using namespace D;

App::App(int &argc, char **argv)
    : QCoreApplication(argc, argv)
{
    m_server = std::make_shared<BaseServer>();
}

int App::start(quint16 port) {
    connect(m_server.get(), &BaseServer::newRequest,this,&App::onNewRequest);

    bool isListening = m_server->listen(QString::number(port));

    if ( !isListening ) {
        qCritical("can not listen on %d!\n", port);
        return -1;
    }

    log("Server listening @ " + QString::number(port));

    return exec();
}

void App::process(std::shared_ptr<Request> req, std::shared_ptr<Response> res)
{
    // Pre-middleware
    {
        foreach(auto w, m_middlewares)
        {
            auto invokable = w();
            auto middleware = std::dynamic_pointer_cast<BaseMiddleware>(invokable);
            middleware->preProcess(req,res);
        }
    }

    QString url = req->url().toDisplayString();
    QStringList path = url.split('/',QString::SkipEmptyParts);

    QString matchedRoute;
    auto route = getRoute(path, &matchedRoute);
    if(route)
    {
        auto invokable = route();
        auto controller = std::dynamic_pointer_cast<BaseController>(invokable);
        if(controller)
        {
            controller->setRoute(matchedRoute);
            controller->process(req, res);
        }
    }

    // Post-middleware
    {
        foreach(auto w, m_middlewares)
        {
            auto invokable = w();
            auto middleware = std::dynamic_pointer_cast<BaseMiddleware>(invokable);
            middleware->postProcess(req,res);
        }
    }

    res->finish(QByteArray());
}

Invokable App::getRoute(const QStringList &path, QString *route)
{
    int current_rating = -1;
    Invokable v = nullptr;

    RouteIterator i = m_routes.constBegin();
    while (i != m_routes.constEnd()) {
        QStringList p = i.key().split('/',QString::SkipEmptyParts);

        if(p.count() == 0 && current_rating < 0)
        {
            current_rating = 0;
            v = i.value(); // Default route '/'
        }
        else
        {
            auto rating = getMatchRating(p, path);
            if(rating > current_rating)
            {
                current_rating = rating;
                v = i.value();

                if(route)
                    *route = i.key();
            }
        }
        ++i;
    }

    return v;
}

int App::getMatchRating(const QStringList &l1, const QStringList &l2)
{
    int rating = 0;

    int count = std::min(l1.count(), l2.count());

    for(int i = 0; i < count; i++)
    {
        if(l1.at(i) == l2.at(i))
            rating++;
    }

    if(rating == 0)
        return -1;

    return rating;
}

bool App::addRouteExInst(QString p, Invokable v)
{
    if(m_routes.contains(p))
    {
        return false;
    }

    m_routes[p] = v;

    return true;
}

void App::addMiddlewareExInst(Invokable v)
{
    m_middlewares.append(v);
}

void App::onNewRequest(std::shared_ptr<Request> req, std::shared_ptr<Response> res)
{
    req->collectData();
    req->getRawRequest()->onEnd([this, req, res](){
        process(req, res);
    });
}


QString App::id()
{
    return "App";
}
