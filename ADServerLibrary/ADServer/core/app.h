#ifndef ADSSERVERAPP_H
#define ADSSERVERAPP_H

#include <QCoreApplication>
#include "common.h"
#include "baseinvokable.h"
#include "baselogger.h"
#include <QHash>
#include <QVector>

namespace D {

typedef std::shared_ptr<BaseInvokable>(*Invokable)();
typedef QHash<QString, Invokable> Routes;
typedef QHash<QString, Invokable>::const_iterator RouteIterator;
typedef QVector<Invokable> Middlewares;

class BaseServer;

class ADSERVERSHARED_EXPORT App : public QCoreApplication, public BaseLogger
{
    Q_OBJECT
public:
    App(int &argc, char **argv);

public:
    int start(quint16 port);
    void process(std::shared_ptr<Request> req, std::shared_ptr<Response> res);

public:
    template<typename T>
    bool addRoute(QString path){
        Invokable v = &BaseInvokable::create<T>;
        return addRouteExInst(path, v);
    }

    template<typename T>
    void addMiddleware(){
        Invokable v = &BaseInvokable::create<T>;
        return addMiddlewareExInst(v);
    }

private:
    Invokable getRoute(const QStringList &path, QString *route = nullptr);
    int getMatchRating(const QStringList &l1 , const QStringList &l2);
    bool addRouteExInst(QString p, Invokable v); // Explicit instantiation of template function addRoute
    void addMiddlewareExInst(Invokable v); // Explicit instantiation of template function addMiddleware

private slots:
    void onNewRequest(std::shared_ptr<Request> req, std::shared_ptr<Response> res);

private:
    Routes m_routes;
    Middlewares m_middlewares;
    std::shared_ptr<BaseServer> m_server;

    // BaseLogger interface
protected:
    QString id() override;
};

} // namespace D
#endif // ADSSERVERAPP_H
