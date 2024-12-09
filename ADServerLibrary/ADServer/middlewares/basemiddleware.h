#ifndef BASEMIDDLEWARE_H
#define BASEMIDDLEWARE_H

#include "export.h"
#include "core/baseinvokable.h"
#include "core/baselogger.h"

namespace D {

class ADSERVERSHARED_EXPORT BaseMiddleware : public BaseInvokable, public BaseLogger
{
    Q_OBJECT

public:
    BaseMiddleware();
    ~BaseMiddleware() override;

public:
    virtual void preProcess(std::shared_ptr<Request>, std::shared_ptr<Response>);
    virtual void postProcess(std::shared_ptr<Request>, std::shared_ptr<Response>);

    // BaseInvokable interface
public:
    void process(std::shared_ptr<Request>, std::shared_ptr<Response>) override;
};

} // namespace D

#endif // BASEMIDDLEWARE_H
