#include "TSHelpTools.h"
#include <QJsonParseError>
#include <QDebug>
#include <QVariant>
#include <QString>
#include "Model/TSGlobalAttribute.h"

TSHelpTools::TSHelpTools()
{

}

bool TSHelpTools::isInvalidJson(QString &checkContent, QString &analysJson)
{
    QJsonParseError parseError;
    QJsonDocument json = QJsonDocument::fromJson(checkContent.toLatin1(), &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        analysJson = QString(json.toJson(QJsonDocument::Compact)); // 格式化
        return false;
    }else{
        qDebug() << "parse-json-error,content: " << checkContent
                 << " Error: " << parseError.errorString();
        return true;
    }
}

bool TSHelpTools::isValidJsonWithPost(const  QByteArray &checkContent, QJsonDocument *analysJson)
{
    QJsonParseError parseError;
    QJsonDocument json = QJsonDocument::fromJson(checkContent, &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        *analysJson = json;
        return true;
    }else{
        qDebug() << "parse-json-error,content: " << checkContent
                 << " Error: " << parseError.errorString();
        return false;
    }
}

bool TSHelpTools::isValidJsonWithGet(const QMap<QByteArray,QByteArray> &mapObject, QJsonDocument *analysJson)
{
    try {
        QMap<QString, QVariant> changeToJson;
        foreach(QByteArray t_key, mapObject.keys()){
            changeToJson.insert(QString(t_key), QVariant(mapObject[t_key]));
        }
        *analysJson = QJsonDocument::fromVariant(QVariant(changeToJson));
        return true;
    } catch (...) {
        return false;
    }
}


QString TSHelpTools::filterJsonPre(QString jsonContent)
{
    if (jsonContent.isEmpty()) return QString();
    QByteArray queryJson = jsonContent.toLatin1();
    return QString(queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, ""));
}


bool TSHelpTools::isPathAlreadyExist(const QString &path)
{
    auto allPathsKey = GlobalStaticPro::bodyDataModel.keys();
    if (allPathsKey.isEmpty()) return false;
    if (allPathsKey.contains(path)) return true;
    return false;
}

bodyStruct TSHelpTools::queryBodyWithPath(const QString &path)
{
    if (!isPathAlreadyExist(path)) {
        bodyStruct body;
        return body;
    }
    return GlobalStaticPro::bodyDataModel[path];
}

QJsonDocument TSHelpTools::changeMapToJson(const QMap<QByteArray,QByteArray> &mapObject)
{
    // QVariant匹配的构造方法只有: QVariant(const QMap<QString, QVariant> &val)
    QMap<QString, QVariant> changeToJson;
    foreach(QByteArray t_key, mapObject.keys()){
        changeToJson.insert(QString(t_key), QVariant(mapObject[t_key]));
    }

    return QJsonDocument::fromVariant(QVariant(changeToJson));
}

