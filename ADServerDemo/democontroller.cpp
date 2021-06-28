#include "democontroller.h"
#include <QJsonObject>
#include <QJsonDocument>

void demoController::get()
{
    QJsonObject o;
    o["Hello"] = "World";

    setContentType("application/json");
    sendResponse(QJsonDocument(o).toJson());
}
