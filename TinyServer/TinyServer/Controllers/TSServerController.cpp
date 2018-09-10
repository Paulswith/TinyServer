#include "TSServerController.h"
#include <QString>

TSServerController::TSServerController(QObject *parent)
    :HttpRequestHandler(parent)
{}


void TSServerController::service(HttpRequest &request, HttpResponse &response)
{
//    emit signal_onnectionInfoToConsole(QString(request.getPath()));
    response.write("receive you requests:\n ", false);
//    (*consoleFunc)(QString("----service-----"));

//    emit signal_onnectionInfoToConsole(QString(request.getBody()));
}
