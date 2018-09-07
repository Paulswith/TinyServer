#ifndef HELLOWORLDCONTROLLER_H
#define HELLOWORLDCONTROLLER_H
#include "httprequesthandler.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

using namespace stefanfrings;

/*
struct sqlData {
    QString method;
    QString path;
    QString rawParam;
    QString paramToJson;
};
*/

class HelloWorldController : public HttpRequestHandler
{
public:
    HelloWorldController(QObject *parent=NULL);
    void service(HttpRequest & request, HttpResponse & response);

private:
    QSqlDatabase db;
    ~HelloWorldController();
};

#endif // HELLOWORLDCONTROLLER_H
