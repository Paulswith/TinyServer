#include "TSSqlConnection.h"
#include <QDebug>
#include "Tools/TSConfigUtil.h"


QString const DB_TYPE = "QSQLITE";
QString const DB_CONNECT_NAME = "SQLITE_DB_CNT";

QSqlDatabase TSSqlConnection::getSqlConnection(bool *isOpen, QSqlError *error)
{
    *isOpen = true;
    QString dbPath = TSConfigUtil::getDatabasePath();
    if (dbPath.isEmpty()) qDebug() << "数据库文件不存在:";
    // 用连接名进行判断是否存在连接
    QSqlDatabase db;
    if (QSqlDatabase::contains(DB_CONNECT_NAME)) {
        qDebug() << "数据连接已经存在,无需创建连接";
        db = QSqlDatabase::database(DB_CONNECT_NAME, true); // boolOpen = true
    }else{
        qDebug() << "数据连接不存在,需创建连接";
        db = QSqlDatabase::addDatabase(DB_TYPE, DB_CONNECT_NAME);
        db.setDatabaseName(dbPath); // 这里才是指定DB文件路径
    }

    if (!db.open()) {
        *isOpen = false;
        if (error != nullptr) *error = db.lastError();
    }
    return db;
}

void TSSqlConnection::closeSqlConnection()
{
    if (QSqlDatabase::contains(DB_CONNECT_NAME)) {
        qDebug() << "数据连接已经存在,进行断开";
        QSqlDatabase::removeDatabase(DB_CONNECT_NAME);
    }
}

