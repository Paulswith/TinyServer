#include "TSHelpTools.h"
#include <QJsonParseError>
#include <QDebug>
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
bool TSHelpTools::isValidJson(QByteArray checkContent, QJsonDocument *analysJson)
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

