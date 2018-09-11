#include "HelloWorkController.h"

HelloWorkController::HelloWorkController(QObject *parent)
    :HttpRequestHandler(parent)
{

}


void HelloWorkController::service(HttpRequest &request, HttpResponse &responce)
{
    responce.write("Hello world!", true);

}
