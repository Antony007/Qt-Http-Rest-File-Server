#include "basecontroller.h"
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

using namespace D;

BaseController::BaseController()
    : BaseInvokable ()
{

}

BaseController::~BaseController()
{

}

void BaseController::setRoute(QString route)
{
    m_route = route;
}

void BaseController::process(std::shared_ptr<Request> request, std::shared_ptr<Response> response)
{
    m_request = request;
    m_response = response;

    m_data.clear();
    m_postData.clear();
    m_params.clear();
    m_queryParams.clear();

    QString url = m_request->url().toDisplayString();
    url = sanitizeUrl(url);

    if(url.startsWith(m_route))
        url = url.remove(0, m_route.count());

    // Get params
    {
        QStringList path = url.split('/',QString::SkipEmptyParts);
        if(!path.isEmpty())
        {
            auto lastElement = path.last();
            lastElement = lastElement.split("?",QString::SkipEmptyParts)[0];
            lastElement = lastElement.trimmed();
            if(lastElement.isEmpty())
                path.removeLast();
            else
                path.last() = lastElement;
        }

        for (int i = 0; i < path.count(); i++)
        {
            m_params.append(path.at(i));
        }
    }

    // Get Query string
    {
        QUrlQuery q(m_request->url());
        auto items = q.queryItems();

        foreach(auto item, items)
        {
            m_queryParams.insert(item.first, item.second);
        }
    }

    // Get post data
    {
        m_postData = m_request->getPostData();
    }

    m_response->setStatus(Response::STATUS_OK); // Set default status of 200

    QString methodName = m_request->getMethod();
    QString param = "";
    if(m_params.count() > 0)
        param = m_params.takeAt(0);

    methodName += param;

    bool success =  QMetaObject::invokeMethod(this,methodName.toStdString().c_str(),Qt::DirectConnection);

    if(!success && !param.isEmpty()) // If unable to find function with param, try to restore param and invoke root method function
    {        
        m_params.insert(0,param);
        success =  QMetaObject::invokeMethod(this,m_request->getMethod().toStdString().c_str(),Qt::DirectConnection);
    }

    if(!success && (m_request->getMethod().compare("options") != 0))
        m_response->setStatus(Response::STATUS_NOT_FOUND);

    m_response->send(m_data);
}

void BaseController::setHeader(const QByteArray &header, const QByteArray &value)
{
    m_response->setHeader(header,value);
}

void BaseController::setContentType(QString type)
{
    m_response->setHeader("Content-Type", type.toUtf8());
}

void BaseController::setStatus(Response::ResponseStatusCode code)
{
    m_response->setStatus(code);
}

void BaseController::sendResponse(QByteArray response)
{
    m_data += response;
}

std::shared_ptr<Response> BaseController::getResponse() const
{
    return m_response;
}

QueryParameters &BaseController::getQueries()
{
    return m_queryParams;
}

UrlParameters &BaseController::getParameters()
{
    return m_params;
}

QByteArray &BaseController::getPostData()
{
    return m_postData;
}

void BaseController::sendJsonResponse(QJsonObject object)
{
    QJsonDocument doc(object);
    setContentType("application/json");
    sendResponse(doc.toJson(QJsonDocument::Compact));
}

void BaseController::sendJsonResponse(QJsonDocument doc)
{
    setContentType("application/json");
    sendResponse(doc.toJson(QJsonDocument::Compact));
}

void BaseController::sendJsonResponse(QJsonArray array)
{
    QJsonDocument doc(array);
    setContentType("application/json");
    sendResponse(doc.toJson(QJsonDocument::Compact));
}

void BaseController::sendFile(QString path)
{
    QFile f(path);
    if(!f.open(QFile::ReadOnly))
    {
        setStatus(Response::STATUS_NOT_FOUND);
        return;
    }

    auto data = f.readAll();
    f.close();

    QMimeType type = db.mimeTypeForFile(path);

    setContentType(type.name());
    sendResponse(data);
}

QString BaseController::sanitizeUrl(QString url)
{
    QString sanitizedUrl = url;

    // Remove duplicate slash
    {
        const bool SANTIZE_ALL = false;
        bool foundSlash = false;
        int index = 0;

        // Remove all
        if(SANTIZE_ALL)
        {
            sanitizedUrl = sanitizedUrl.replace("//","/");
        }
        else // Only remove from beginning
        {
            while (true) {
                if(sanitizedUrl.at(index) == "/")
                {
                    if(!foundSlash)
                    {
                        foundSlash = true;
                        index++;
                    }
                    else
                    {
                        sanitizedUrl.remove(index,1);
                    }
                }
                else
                    break;

                if(index >= sanitizedUrl.size())
                    break;
            }
        }
    }

    return sanitizedUrl;
}

QString BaseController::id()
{
    return "Controller";
}
