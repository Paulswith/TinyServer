#ifndef TSGLOBALATTRIBUTE_H
#define TSGLOBALATTRIBUTE_H

#include <QStringList>
#include <QJsonDocument>

namespace GlobalStaticPro {
    // 当前已有path， 区分大小写
    extern QStringList alreadyExistPaths;
    extern int serverPort;
}

//
struct bodyStruct{
    QString path;
    QString method;
    QJsonDocument reqJson;
    QJsonDocument rspJson;
};


class TSGlobalAttribute
{
public:
    TSGlobalAttribute();
};

#endif // TSGLOBALATTRIBUTE_H
