#include "basemiddleware.h"

using namespace D;

BaseMiddleware::BaseMiddleware()
    : BaseInvokable ()
{

}

BaseMiddleware::~BaseMiddleware()
{

}

void BaseMiddleware::preProcess(std::shared_ptr<Request>, std::shared_ptr<Response>)
{
    return;
}

void BaseMiddleware::postProcess(std::shared_ptr<Request>, std::shared_ptr<Response>)
{
    return;
}


void BaseMiddleware::process(std::shared_ptr<Request>, std::shared_ptr<Response>)
{
    return;
}
