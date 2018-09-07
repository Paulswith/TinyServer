#include <iostream>
#include <QCoreApplication>
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <httplistener.h>
#include <httprequesthandler.h>
#include "HelloWorldController.h"

using namespace std;
using namespace stefanfrings;

pair<bool,QString> searchConfigFile(QString targetName, QString fileDir="Config");

int main(int argc, char *argv[])
{

    QCoreApplication app(argc, argv);
    pair<bool,QString> searchResult = searchConfigFile(QString("Demo1_tinyServer"));

    qDebug() << "configPath: " << searchResult.second;
    if (!searchResult.first) {
        qDebug() << "unfound search .ini file.";
        return 0;
    }
    QSettings *listenerSettings =
            new QSettings(searchResult.second, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");
    qDebug() << "Config loaded";

//    new HttpListener(listenerSettings, new HttpRequestHandler(&app), &app);
    new HttpListener(listenerSettings, new HelloWorldController(&app), &app);

    return app.exec();
}


pair<bool,QString> searchConfigFile(QString targetName, QString fileDir) {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    qDebug() << "appName: " << appName
             << "binDir:" << binDir;
    QFile file;
    file.setFileName(binDir+QString("/%1.ini").arg(targetName));
    if (!file.exists()) {
        file.setFileName(binDir+QString("/%1/%2.ini").arg(fileDir).arg(targetName));
        if (!file.exists()) {
            file.setFileName(binDir+QString("/../%1/%2.ini").arg(fileDir).arg(targetName));
            if (!file.exists()) {
                file.setFileName(binDir+"/../"+appName+QString("/%1/%2.ini").arg(fileDir).arg(targetName));
                if (!file.exists()) {
                    file.setFileName(binDir+"/../../"+appName+QString("/%1/%2.ini").arg(fileDir).arg(targetName));
                    if (!file.exists()) {
                        file.setFileName(binDir+"/../../../../../"+appName+QString("/%1/%2.ini").arg(fileDir).arg(targetName));
                        if (!file.exists()) {
                            file.setFileName(QDir::rootPath()+QString("%1/%2.ini").arg(fileDir).arg(targetName));
                        }
                    }
                }
            }
        }
    }
    if (file.exists()) {
        QString configFileName=QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        pair<bool, QString> founded(true, configFileName);
        return founded;
    }

    qFatal("config file not found");
    pair<bool, QString> notfound(false, QString());
    return notfound;
}
