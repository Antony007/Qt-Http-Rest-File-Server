#ifndef BASEINVOKABLE_H
#define BASEINVOKABLE_H

#include <QObject>

namespace ADServer {

class Request;
class Response;

class BaseInvokable : public QObject
{
    Q_OBJECT
public:
    explicit BaseInvokable();
    virtual ~BaseInvokable();

public:
    template<class T>
    static std::shared_ptr<BaseInvokable> create() {return std::make_shared<T>();}

public:
    virtual void process(std::shared_ptr<Request> request,
                         std::shared_ptr<Response> response) = 0;
};

} // namespace ADServer

#endif // BASEINVOKABLE_H
