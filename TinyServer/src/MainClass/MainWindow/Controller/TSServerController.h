#ifndef TSSERVERCONTROLLER_H
#define TSSERVERCONTROLLER_H

#include <QString>
#include "httprequesthandler.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"

using AppConfigs::PrintType;
using namespace stefanfrings;

class TSServerController : public HttpRequestHandler
{
    Q_OBJECT
public:
    TSServerController(QObject *parent = nullptr);
    void service(HttpRequest& request, HttpResponse& response);

private:
    QByteArray readFileWithPath(const QString& path);

signals:
    void signalWithPrintToConsole(QString str, PrintType printTyle = PrintType::printStdout);
};

#endif // TSSERVERCONTROLLER_H
