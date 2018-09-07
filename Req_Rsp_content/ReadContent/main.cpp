#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QJsonDocument>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>


QString const dbPath = "/home/dobby/Code/Cpp/Qt/Req_Rsp_content/ReadContent/Data/demo1.db";
QString const debug_pathPrefix="/../ReadContent"; // complement the path when debug-env
//QString const pathSuffix = "%1/Data/interaction.txt";
QString const pathSuffix = "%1/Data/a.txt";

QString readContent();


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    /*
    QString content = readContent();

    if (content.size() == 0) {
        return 0;
    }

    // analysis string tojson:
    qDebug() << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
    QJsonDocument jsondata = QJsonDocument::fromJson(content.toUtf8());
    qDebug() << jsondata;
    if (jsondata.isNull()) {
        return 0;
    }
    */

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "***************:\ndb not open!"
                 << db.lastError()
                 << db.drivers();
    }
    QSqlQuery query;
    query.prepare("select * from requests");
    if (!query.exec()) {
        qDebug() << query.lastError();
    }else{
        while(query.next()) {
            // filter  sql(json(''))  to json format
            QByteArray OrgJson = [&]() -> QByteArray {
                QByteArray queryJson = query.value(3).toByteArray();
                return queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, "");
            }();

            QJsonDocument reqJson = QJsonDocument::fromJson(OrgJson);
            qDebug() << reqJson << " " << OrgJson;
        }
    }

    return 0;
}


QString readContent() {
    QString filePath = QDir().absolutePath() + pathSuffix.arg(debug_pathPrefix);
    qDebug() << filePath;

    QFile contentFile(filePath);
    // open file:
    if (!contentFile.exists()) {
        qDebug() << "File don't exists.";
        return QString();
    } else if (!contentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File can't open.";
        return QString();
    }

    QTextStream contentReader(&contentFile);
    QString holder(contentReader.readAll());

    qDebug() << holder;
    contentFile.close();
    return holder;
}
