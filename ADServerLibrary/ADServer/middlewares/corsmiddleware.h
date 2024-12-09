#ifndef CORSMIDDLEWARE_H
#define CORSMIDDLEWARE_H

#include "export.h"
#include "basemiddleware.h"

namespace D {

class ADSERVERSHARED_EXPORT corsMiddleware : public BaseMiddleware
{
    // BaseMiddleware interface
public:
    void preProcess(std::shared_ptr<Request>, std::shared_ptr<Response> response) override;

public:
    static void addMethod(QString method);
    static void removeMethod(QString method);
    static QVector<QString> methods();

    static void addHeader(QString header);
    static void removeHeader(QString header);
    static QVector<QString> headers();

    static void setOrigin(QString origin);

private:
    QString vectorToDelimited(QVector<QString> data);

private:
    static QString m_origin;
    static QVector<QString> m_methods;
    static QVector<QString> m_headers;
};

} // namespace D

#endif // CORSMIDDLEWARE_H
