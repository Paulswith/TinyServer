#include <QDebug>
#include <QSqlQuery>
#include "MainClass/Tools/TSSqlConnection.h"
#include "MainClass/Tools/TSConfigUtil.hpp"
#include "MainClass/Tools/TSHelpTools.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"


QString const DB_TYPE = "QSQLITE";
QString const DB_TABLE_NAME = "body_interaction";
QString const DB_CONNECT_NAME = "SQLITE_DB_CNT";

/*all - sql strings*/
const QString sql_queryall = QString("select * from %1").arg(DB_TABLE_NAME);
const QString sql_queryallPath = QString("select path from %1").arg(DB_TABLE_NAME);
const QString sql_querysingle = QString("select count(*) from %1 where path=:A").arg(DB_TABLE_NAME); // 不带引号
const QString sql_querysingleItems = QString("select * from %1 where path=:A").arg(DB_TABLE_NAME); // 不带引号
const QString sql_insertsingle = QString("insert into %1 values(:A, :B, :C, :D)").arg(DB_TABLE_NAME);
const QString sql_updatesingle = QString("insert into %1 values(:A, :B, :C, :D)").arg(DB_TABLE_NAME);
const QString sql_deleteOneRow = QString("DELETE FROM %1 WHERE path=:A ").arg(DB_TABLE_NAME);  // delete 不带引号


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

QList<QList<QStandardItem *>> TSSqlConnection::updateDataModel()
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
//        GlobalStaticPro::mainDataModel.clear();
        while(query.next()) {
            auto t_path = query.value(0).toString();
            auto t_method = query.value(1).toString();
//            auto t_req = TSHelpTools::filterJsonPre(query.value(2).toString());
//            auto t_rsp = TSHelpTools::filterJsonPre(query.value(3).toString());

            auto t_req = TSHelpTools::filterJsonPre(query.value(2).toString().toUtf8());
            auto t_rsp = TSHelpTools::filterJsonPre(query.value(3).toString().toUtf8());
            // 存储的全局模型
            bodyStruct bodies = {t_path, t_method,
                                 QJsonDocument::fromJson(t_req),
                                 QJsonDocument::fromJson(t_rsp)};
            // 获取的Items
            QList<QStandardItem *> items = {(new QStandardItem(t_path)),
                                           (new QStandardItem(t_method)),
                                           (new QStandardItem(QString::fromUtf8(t_req))),
                                           (new QStandardItem(QString::fromUtf8(t_rsp))),};
            allBodyItems << items;
            GlobalStaticPro::bodyDataModel[t_path] = bodies;
        }
    }
    return allBodyItems;
}

bool TSSqlConnection::isPathInDBsets(QString &path)
{
//    bool isExist = true; // 初始化为存在不允许添加
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return true;
    }

    QSqlQuery query(db);
    query.prepare(sql_querysingle);
    query.bindValue(":A", path);
    if (!query.exec()) {
        qDebug() << "query.exec Error: " << query.lastError();
        return true;
    }else if (query.next()) {
        int countExist = query.value(0).toInt();
        qDebug() << "query.hasItemExist Error(Count): " << countExist;
        if (countExist != 0) return true;
    }
    return false;
}

bool TSSqlConnection::insertBodyData(const QStringList &insertList)
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
        query.bindValue(":C", QString("json('%1')").arg(insertList.at(2)));
        query.bindValue(":D", QString("json('%1')").arg(insertList.at(3)));

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
    }catch (...){
        qDebug() << "insert Exception(...): ";
        db.rollback();
        return isHanlderSuc;
    }

    return isHanlderSuc;
}

bool TSSqlConnection::updateBodyDataWithPath(const QStringList &updateList)
{
    // update语法的时候, json前缀似乎加不上~~ 目前先用delete 再insert了... 不过前面有json校验等, 基本不可能失败
    if (updateList.count() != 4) return false;
    deleteExistPaths(updateList.at(0));
    return insertBodyData(updateList);
}

void TSSqlConnection::deleteExistPaths(const QString &path)
{
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return;
    }

    QSqlQuery query(db);
    query.prepare(sql_deleteOneRow);
    query.bindValue(":A", path);
    if (!query.exec()) {
        qDebug() << "query-exec-Error: " << query.lastError().text();
        db.rollback();
    }else{
        qDebug() << "query-exec-suc!";
        db.commit();
        query.finish();
    }
}

bodyStruct TSSqlConnection::queryBodyItemWithPath(const QString path)
{
    bodyStruct bodies;
    QSqlError error;
    bool isOpen;
    QSqlDatabase db = getSqlConnection(&isOpen, &error);
    if (!isOpen) {
        qDebug() << "getSqlConnection-Error: " << error.text();
        return bodies;
    }

    QSqlQuery query(db);
    query.prepare(sql_querysingleItems);
    query.bindValue(":A", path);
    if (!query.exec()) {
        qDebug() << "query-exec-Error: " << query.lastError().text();
        return bodies;
    }else{
        while(query.next()) {
            bodies.path = query.value(0).toString();
            bodies.method = query.value(1).toString();
            bodies.reqJson = QJsonDocument::fromJson(TSHelpTools::filterJsonPre(query.value(2).toByteArray()));
            bodies.rspJson = QJsonDocument::fromJson(TSHelpTools::filterJsonPre(query.value(3).toByteArray()));
        query.finish();
        }
        return bodies;
    }
}


void TSSqlConnection::closeSqlConnection()
{
    if (QSqlDatabase::contains(DB_CONNECT_NAME)) {
        qDebug() << "数据连接已经存在,进行断开";
        QSqlDatabase::removeDatabase(DB_CONNECT_NAME);
    }
}
