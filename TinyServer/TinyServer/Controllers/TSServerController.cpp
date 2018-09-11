#include "TSServerController.h"
#include <QString>
#include "Model/TSGlobalAttribute.h"
#include "Tools/TSHelpTools.h"
#include "Tools/TSSqlConnection.h"

TSServerController::TSServerController(QObject *parent)
    :HttpRequestHandler(parent)
{}


void TSServerController::service(HttpRequest &request, HttpResponse &response)
{
    emit signal_connectionInfoToConsole(QString("+new request:[%1] -> \n%2").
                                        arg(QString(request.getPath())).arg(QString(request.getBody())));

    if (!GlobalStaticPro::alreadyExistPaths.contains(request.getPath())) {
        response.setStatus(404, "Not found");
        response.write("The URL is wrong, no such path.", true);
        emit signal_connectionInfoToConsole("-Check failure:[404] -> The URL is wrong, no such path.");
        return;
    }

    if (request.getMethod() != "POST") {
        response.setStatus(405, "Method Not Allowed");
        response.write("Only support POST Method.", true);
        emit signal_connectionInfoToConsole("-Check failure:[405] -> Only support POST Method.");
        return;
    }

    //1. body转json异常则400
    QJsonDocument bodyToJson;
    bool suc = TSHelpTools::isValidJson(request.getBody(), &bodyToJson);
    if (!suc) {
        response.setStatus(400, "Bad Request");
        response.write("Request-body unidentifiable", true);
        emit signal_connectionInfoToConsole("-Check failure:[400] -> Request-body unidentifiable.");
        return;
    };

    // 2.比对设置的req
    bodyStruct hanlderBody = TSSqlConnection::queryBodyItemWithPath(request.getPath());
    bool isRequestEqual = (bodyToJson == hanlderBody.reqJson);
    if (!isRequestEqual){
        response.setStatus(400, "Bad Request");
        response.write("Request body mismatch;", true);
        emit signal_connectionInfoToConsole("-Check failure:[400] -> Request body mismatch");
        return;
    }
    QByteArray retContent = hanlderBody.rspJson.toJson(QJsonDocument::Indented);
    emit signal_connectionInfoToConsole(QString("-Check succeed:[200] -> \\n%1").arg(QString(retContent)));
    response.write(retContent, true);
}
