#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "TSServerController.h"
#include "MainClass/Main/Model/TSGlobalAttribute.h"
#include "MainClass/Tools/TSHelpTools.h"
#include "MainClass/Tools/TSSqlConnection.h"


TSServerController::TSServerController(QObject *parent)
    :HttpRequestHandler(parent)
{}


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

    emit signal_connectionInfoToConsole("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    emit signal_connectionInfoToConsole(QString("+new request:[%1] -> \n%2").
                                        arg(QString(request.getPath())).arg(QString(request.getBody())));

    if (!TSHelpTools::isPathAlreadyExist(request.getPath())) {
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
    bodyStruct hanlderBody = TSHelpTools::queryBodyWithPath(request.getPath());
    bool isRequestEqual = (bodyToJson == hanlderBody.reqJson);
    if (!isRequestEqual){
        response.setStatus(400, "Bad Request");
        response.write("Request body mismatch;", true);
        emit signal_connectionInfoToConsole("-Check failure:[400] -> Request body mismatch");
        return;
    }
    QByteArray retContent = hanlderBody.rspJson.toJson(QJsonDocument::Indented);
    emit signal_connectionInfoToConsole(QString("#Check succeed:[%1] -> \n%2").
                                        arg(response.getStatusCode()).
                                        arg(QString(retContent)));
    response.write(retContent, true);
}
