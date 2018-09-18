#ifndef TSGLOBALATTRIBUTE_H
#define TSGLOBALATTRIBUTE_H

#include <QStringList>
#include <QJsonDocument>
#include <QMap>

//
struct bodyStruct{
    QString path;
    QString method;
    QJsonDocument reqJson;
    QJsonDocument rspJson;
};

// 请求方式
enum RequestMethod {
    POST,
    GET
};

namespace GlobalStaticPro {
    // 当前已有path， 区分大小写
//    extern QStringList alreadyExistPaths;
//    extern QList<bodyStruct> mainDataModel;
    extern QMap<QString, bodyStruct> bodyDataModel;
    extern int serverPort;
}




class TSGlobalAttribute
{
public:
    TSGlobalAttribute();
};

#endif // TSGLOBALATTRIBUTE_H
