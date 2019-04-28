#ifndef HELLOWORKCONTROLLER_H
#define HELLOWORKCONTROLLER_H
#include "httpconnectionhandler.h"

using namespace stefanfrings;

class HelloWorkController : public HttpRequestHandler
{
    Q_OBJECT
public:
//    HelloWorkController(QObject* parent=0);
    HelloWorkController(QObject* parent=NULL);
//    HelloWorldController(QObject* parent=0);
    void service(HttpRequest & request, HttpResponse & responce);
};

#endif // HELLOWORKCONTROLLER_H
