#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "TSServerController.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"
#include "MainClass/Tools/TSHelpTools.h"
#include "MainClass/Tools/TSSqlConnection.h"


TSServerController::TSServerController(QObject *parent)
    : HttpRequestHandler(parent)
{

}


QByteArray TSServerController::readFileWithPath(const QString& path) {
    QByteArray retContent;
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "读取文件失败.";
        return retContent;
    }
//    QTextStream readStream(&file);
    QTextStream readStream(&file);
    retContent = readStream.readAll().toUtf8();
//    qDebug() << retContent;
    return retContent;
}


void TSServerController::service(HttpRequest &request, HttpResponse &response)
{

    signalWithPrintToConsole("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    signalWithPrintToConsole(QString("+new request:[%1] -> \n%2").
                                        arg(QString(request.getPath())).arg(QString(request.getBody())));

    if (!TSHelpTools::isPathAlreadyExist(request.getPath())) {
        response.setStatus(404, "Not found");
        response.write("The URL is wrong, no such path.", true);
        signalWithPrintToConsole("-Check failure:[404] -> The URL is wrong, no such path.", PrintType::printStderr);
        return;
    }

    if (request.getMethod() != "POST") {
        response.setStatus(405, "Method Not Allowed");
        response.write("Only support POST Method.", true);
        signalWithPrintToConsole("-Check failure:[405] -> Only support POST Method.", PrintType::printStderr);
        return;
    }

    //1. body转json异常则400
    QJsonDocument bodyToJson;
    bool suc = TSHelpTools::isValidJson(request.getBody(), &bodyToJson);
    if (!suc) {
        response.setStatus(400, "Bad Request");
        response.write("Request-body unidentifiable", true);
        signalWithPrintToConsole("-Check failure:[400] -> Request-body unidentifiable.", PrintType::printStderr);
        return;
    };

    // 2.比对设置的req
    bodyStruct hanlderBody = TSHelpTools::queryBodyWithPath(request.getPath());
    bool isRequestEqual = (bodyToJson == hanlderBody.reqJson);
    if (!isRequestEqual){
        response.setStatus(400, "Bad Request");
        response.write("Request body mismatch;", true);
        signalWithPrintToConsole("-Check failure:[400] -> Request body mismatch", PrintType::printStderr);
        return;
    }
    QByteArray retContent = hanlderBody.rspJson.toJson(QJsonDocument::Indented);
    signalWithPrintToConsole(QString("#Check succeed:[%1] -> \n%2").
                                        arg(response.getStatusCode()).
                                        arg(QString(retContent)),
                             PrintType::printStdsuc);
    response.write(retContent, true);
}
