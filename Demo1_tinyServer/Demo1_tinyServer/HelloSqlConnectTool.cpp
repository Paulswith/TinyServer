#include "HelloSqlConnectTool.h"
#include <QDebug>


HelloSqlConnectTool::HelloSqlConnectTool(QObject *parent) : QObject(parent)
{}

QSqlDatabase HelloSqlConnectTool::initialDataBase(QString dbPath, QString driverType)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(driverType);
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "***************:\ndb not open!"
                 << db.lastError();
    }
    return db;
}

