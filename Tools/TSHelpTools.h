#ifndef TSHELPTOOLS_H
#define TSHELPTOOLS_H

#include <QString>
#include <QJsonDocument>
#include <QMap>
#include "Model/TSGlobalAttribute.h"

class TSHelpTools
{
public:
    TSHelpTools();
    // 验证是否为非法JSON
    static bool isInvalidJson(QString &checkContent, QString &analysJson);
    static bool isValidJsonWithPost(const QByteArray &checkContent, QJsonDocument *analysJson);
    static bool isValidJsonWithGet(const QMap<QByteArray,QByteArray> &mapObject, QJsonDocument *analysJson);

    // 过滤json('')
    static QString filterJsonPre(QString jsonContent);

    // 查询 链接路径是否存在('')
    static bool isPathAlreadyExist(const QString &path);

    static bodyStruct queryBodyWithPath(const QString &path);

    static QJsonDocument changeMapToJson(const QMap<QByteArray,QByteArray> &mapObject);
};

#endif // TSHELPTOOLS_H
