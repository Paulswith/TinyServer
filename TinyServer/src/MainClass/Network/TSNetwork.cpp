#include <QException>
#include "TSNetWork.h"
#include "MainClass/Tools/TSHelpTools.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"

TSNetWork::TSNetWork(TSConsole *console):
    consoleInstance(console)
{
    connect(this,
            &TSNetWork::signalWithPrint,
            consoleInstance,
            &TSConsole::slotWithprint);
}

/* ~~~~~~~~~~~~~~~~~~manager server to listen or not~~~~~~~~~~~~~~~~~~ */
bool TSNetWork::startServerListenWithConfig(const QString& configPath, QString& errorMsg)
{
    //启动条件, 为空 或是 非监听状态
    if (nullptr != serverListener && serverListener->isListening()) {
        errorMsg = "server already listening";
        return false;
    }
//    auto configPath  = TSConfigUtil::getConfigPath();
    if (!TSHelpTools::isPathExist(configPath)) {
        errorMsg = "Can not find config path";
        return false;
    }
    try {
        QSettings *listenerSettings = new QSettings(configPath, QSettings::IniFormat);
        listenerSettings->beginGroup(AppConfigs::kIniConfigGroupName);
        requestHandlerController = new TSServerController();
        connect(requestHandlerController,
                &TSServerController::signalWithPrintToConsole,
                consoleInstance,
                &TSConsole::slotWithprint);
        serverListener = new HttpListener(listenerSettings, requestHandlerController, this);
        listenerSettings->endGroup();
    } catch (const QException& ex) {
        errorMsg = QString::fromUtf8(ex.what());
        return false;
    } catch (...) {
        errorMsg = "Unknow Exception";
        return  false;
    }
    return true;
}

void TSNetWork::suspendServerListen()
{
    // 不为空, 且在监听中, 则可以停止
    if (nullptr != serverListener && serverListener->isListening()) {
        serverListener->close();
        disconnect(requestHandlerController, &TSServerController::signalWithPrintToConsole,
                   consoleInstance, &TSConsole::slotWithprint);
        serverListener = nullptr;
        requestHandlerController = nullptr;
    }
}

quint16 TSNetWork::getListenPort()
{
    return  serverListener->serverPort();
}


TSNetWork::~TSNetWork()
{
    suspendServerListen();
//    if (nullptr != serverListener) delete serverListener;
//    if (nullptr != requestHandlerController) delete requestHandlerController;
    if (nullptr != consoleInstance) delete consoleInstance;
}
