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
    RequestMethod requestModel;
    emit signal_connectionInfoToConsole(QString("+new request:[%1] -> \n%2").
                                        arg(QString(request.getPath())).arg(QString(request.getBody())));

    if (!TSHelpTools::isPathAlreadyExist(request.getPath())) {
        response.setStatus(404, "Not found");
        response.write("The URL is wrong, no such path.", true);
        emit signal_connectionInfoToConsole("-Check failure:[404] -> The URL is wrong, no such path.");
        return;
    }
    // 仅支持 post get
    QString reqMethod = QString(request.getMethod());
    if ((reqMethod != "POST" )  && (reqMethod != "GET")) {
        request.getParameterMap();
        response.setStatus(405, "Method Not Allowed");
        response.write("Only support POST-GET Method.", true);
        emit signal_connectionInfoToConsole("-Check failure:[405] -> Only support POST-GET Method.");
        return;
    }
    requestModel = request.getMethod()=="POST"? RequestMethod::POST : RequestMethod::GET;

    //1. body转json异常则400
    QJsonDocument bodyToJson;
    bool suc;
    if (requestModel == RequestMethod::GET) {
        suc = TSHelpTools::isValidJsonWithGet(request.getParameterMap(), &bodyToJson);
    }else{
        suc = TSHelpTools::isValidJsonWithPost(request.getBody(), &bodyToJson);
    }
    if (!suc) {
        response.setStatus(400, "Bad Request");
        response.write("Request-body unidentifiable", true);
        emit signal_connectionInfoToConsole("-Check failure:[400] -> Request-body unidentifiable.");
        return;
    };
// TODO: 需要修改存储, POST 和 GET  各一张表, tableView的时候拿过来拼成同个数据源

    // 2.比对设置的req
    bodyStruct hanlderBody = TSHelpTools::queryBodyWithPath(request.getPath());
    bool isRequestEqual = (bodyToJson == hanlderBody.reqJson);
    if (!isRequestEqual){
        response.setStatus(400, "Bad Request");
        response.write("Request body mismatch;", true);
        emit signal_connectionInfoToConsole("-Check failure:[400] -> Request body mismatch");
        return;
    }
    QByteArray retContent = hanlderBody.rspJson.toJson(QJsonDocument::Indented);
    emit signal_connectionInfoToConsole(QString("#Check succeed:[200] -> \n%1").arg(QString(retContent)));
    response.write(retContent, true);
}
