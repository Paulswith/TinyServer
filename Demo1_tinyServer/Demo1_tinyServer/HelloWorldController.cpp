#include "HelloWorldController.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QString>
#include <QVariantList>
#include <QSqlQuery>
#include "HelloSqlConnectTool.h"


QString const dbPath = "/home/dobby/Code/Cpp/Qt/Req_Rsp_content/ReadContent/Data/demo1.db";
HelloWorldController::HelloWorldController(QObject *parent)
    :HttpRequestHandler(parent)
{}

void HelloWorldController::service(HttpRequest &request, HttpResponse &response)
{
    QSqlDatabase db = HelloSqlConnectTool::initialDataBase(dbPath);
    response.write("receive you requests:\n ", false);

    QJsonParseError parseError;
    if (request.getMethod() != "POST") {
        return;
    }

    // ********** arse to json: suss **********:
    QJsonDocument jsonData = QJsonDocument::fromJson(request.getBody(), &parseError);
    if (parseError.error != QJsonParseError::NoError || jsonData.isNull()) {
        qDebug() << "Parse exc: " << parseError.errorString() << "\n"
                 << "data:" << request.getBody();
        return;
    }
    qDebug() << "parse suc: " << jsonData;

    if (!db.open()) {
        qDebug() << "DB don't open.!";
        return;
    }

    // ********** try insert to sql **********:
    // create table requests(path TEXT primary key,method TEXT not null, reqParam  TEXT, reqJson JSON);
    QSqlQuery query;

    // place holder the sql values, the id is autoincrement so setit to NULL
    QString preInsert = "insert into requests values(:A, :B, :C, :D)";
    query.prepare(preInsert);   // open - preinsert:
    query.bindValue(":A", QString(request.getPath()));
    query.bindValue(":B", QString(request.getMethod()));
    query.bindValue(":C", QString(request.getBody()));
    query.bindValue(":D", QString("json('%1')").arg(QString(jsonData.toJson())));;
    // exe
    if (!query.exec()) {
        qDebug() <<  "insert faild:" << query.lastError();
        db.rollback();
    }else{
        qDebug() << "insert succed:";
        db.commit();
    }

    // query all :
    query.prepare("select * from requests");
    if (!query.exec()) {
        qDebug() << query.lastError();
        response.write("Write error.", true);
    }else{

        QString retContent;
        while(query.next()) {
            QString path = query.value(0).toString();
            QString method = query.value(1).toString();
            QString reqParam = query.value(2).toString();
            QString reqJson = [&]() -> QString {
                QByteArray queryJson = query.value(3).toByteArray();
                return QString(queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, ""));
            }();
//            QString reqJson = query.value(3).toString();
            retContent += QString("Path=%1 Method=%2 reqParam=%3 reqJson=%4 \n").
                        arg(path).arg(method).arg(reqParam).arg(reqJson);
        }
        qDebug() << retContent;
        response.write(retContent.toLatin1(), true);
    }

}


HelloWorldController::~HelloWorldController()
{
    if (db.open()) {
        db.close();
//        delete db;
    }
}
