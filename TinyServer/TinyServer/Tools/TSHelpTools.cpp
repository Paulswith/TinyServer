#include "TSHelpTools.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QDebug>
#include "Model/TSGlobalAttribute.h"

TSHelpTools::TSHelpTools()
{

}

bool TSHelpTools::isInvalidJson(QString &checkContent)
{
    QJsonParseError parseError;
    QJsonDocument::fromJson(checkContent.toLatin1(), &parseError);
    if (parseError.error == QJsonParseError::NoError) {
        return false;
    }else{
        qDebug() << "parse-json-error,content: " << checkContent
                 << " Error: " << parseError.errorString();
        return true;
    }
}

QString TSHelpTools::filterJsonPre(QString jsonContent)
{
    if (jsonContent.isEmpty()) return QString();
    QByteArray queryJson = jsonContent.toLatin1();
    return QString(queryJson.replace(queryJson.size()-2, 2, "").replace(0, 6, ""));
}


bool TSHelpTools::isPathAlreadyExist(QString & path)
{
//    using namespace TSGlobalModel;
    if (GlobalStaticPro::alreadyExistPaths.isEmpty()) return false;
    if (GlobalStaticPro::alreadyExistPaths.contains(path, Qt::CaseInsensitive)) return true;
    return false;
}
