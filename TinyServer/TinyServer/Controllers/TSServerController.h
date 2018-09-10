#ifndef TSSERVERCONTROLLER_H
#define TSSERVERCONTROLLER_H

#include "httprequesthandler.h"
#include <QString>
//#include "MainView/TSMainWindow.h"

using namespace stefanfrings;


class TSServerController : public HttpRequestHandler
{
//    Q_OBJECT
public:
    TSServerController(QObject *parent=NULL);
    void service(HttpRequest & request, HttpResponse & response);

//signals:
//    void signal_onnectionInfoToConsole(QString str);

};

#endif // TSSERVERCONTROLLER_H
