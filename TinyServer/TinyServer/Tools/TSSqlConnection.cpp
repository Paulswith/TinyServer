#include "TSSqlConnection.h"
#include <QDebug>
#include "Tools/TSConfigUtil.h"
#include <QSqlQuery>


QString const DB_TYPE = "QSQLITE";
QString const DB_TABLE_NAME = "requests";
QString const DB_CONNECT_NAME = "SQLITE_DB_CNT";

/*all - sql strings*/
const QString sql_queryall = QString("select * from %1").arg(DB_TABLE_NAME);
const QString sql_querysingle = QString("select * from %1 where path=':A'").arg(DB_TABLE_NAME);
const QString sql_insertsingle = QString("insert into %1 values(:A, :B, :C, :D)").arg(DB_TABLE_NAME);


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

QList<QList<QStandardItem *>> TSSqlConnection::getAllBodyItems()
{
    QList<QList<QStandardItem *>> allBodyItems;
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return allBodyItems;
    }

    QSqlQuery query(db);
    query.prepare(sql_queryall);

    if (!query.exec()) {
        qDebug() << "query.exec Error: " << query.lastError();
        return allBodyItems;
    }else{
        while(query.next()) {
            QList<QStandardItem *> items;
            QStandardItem *itemPath = new QStandardItem(query.value(0).toString());
            QStandardItem *method = new QStandardItem(query.value(1).toString());
            QStandardItem *reqParam = new QStandardItem(query.value(2).toString());
            // 把json('') 字符替换
            QStandardItem *reqJson = new QStandardItem( [&]() -> QString {
                                    QByteArray queryJson = query.value(3).toByteArray();
                                    return QString(queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, ""));
                                                        }());
            items <<itemPath << method << reqParam << reqJson;
            allBodyItems << items;
        }
    }
    return allBodyItems;
}

bool TSSqlConnection::isPathInDBsets(QString &path)
{
    bool isExist = true; // 初始化为存在不允许添加
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return isExist;
    }

    QSqlQuery query(db);
    query.prepare(sql_querysingle);
    query.bindValue(":A", path);
    if (!query.exec()) {
        qDebug() << "query.exec Error: " << query.lastError();
        return isExist;
    }else if (query.next()) {
        qDebug() << "query.hasItemExist Error: " << query.value(0).toString();
        return isExist;
    }else{
        isExist = false;
    }
    return isExist;
}

bool TSSqlConnection::insertBodyData(QStringList &insertList)
{
    bool isHanlderSuc = false;
    if (insertList.count() != 4) return isHanlderSuc;
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return isHanlderSuc;
    }

    try {
        QSqlQuery query(db);
        query.prepare(sql_insertsingle);
        query.bindValue(":A", insertList.at(0));
        query.bindValue(":B", insertList.at(1));
        query.bindValue(":C", insertList.at(2));
        query.bindValue(":D", insertList.at(3));

        if (!query.exec()) {
            qDebug() << "query.exec Error: " << query.lastError();
            db.rollback();
            return isHanlderSuc;
        }else{
            isHanlderSuc = true;
            db.commit();
        }
    } catch (const std::exception &exc) {  // 这个方法只能捕获继承自Std::
        qDebug() << "insert Exception: " << exc.what();
        db.rollback();
        return isHanlderSuc;
    }
    /*
    catch (...){
        qDebug() << "insert Exception(...): ";
        db.rollback();
        return isHanlderSuc;
    }*/

    return isHanlderSuc;
}


void TSSqlConnection::closeSqlConnection()
{
    if (QSqlDatabase::contains(DB_CONNECT_NAME)) {
        qDebug() << "数据连接已经存在,进行断开";
        QSqlDatabase::removeDatabase(DB_CONNECT_NAME);
    }
}

