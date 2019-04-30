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


namespace GlobalStaticPro {
    // 当前已有path， 区分大小写
//    extern QStringList alreadyExistPaths;
//    extern QList<bodyStruct> mainDataModel;
    extern QMap<QString, bodyStruct> bodyDataModel;
    extern int serverPort;
}

namespace AppConfigs {
    extern const QString kIniConfigGroupName; // ini配置组名

    // 控制台颜色
    enum PrintType {
        printStdsuc, // 成功
        printStderr, // 失败
        printStdout,  // 标准、普通
        printShine  //
    };
}    



#endif // TSGLOBALATTRIBUTE_H
