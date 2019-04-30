#ifndef TSNETWORK_H
#define TSNETWORK_H


#include "httplistener.h"
#include "MainClass/MainWindow/View/TSConsole.h"
#include "MainClass/MainWindow/Controller/TSServerController.h"
#include "MainClass/AppConfig/TSGlobalAttribute.h"

using AppConfigs::PrintType;
using stefanfrings::HttpListener;

class TSNetWork: public QObject
{
    Q_OBJECT
public:
     TSNetWork(TSConsole *console);
    ~TSNetWork();
public: /* public methods */
    /* manager server to listen or not  */
    bool startServerListenWithConfig(const QString& configPath, QString& errorMsg);
    void suspendServerListen();
    quint16 getListenPort();

private: /* properties */
    HttpListener *serverListener = nullptr;
    TSServerController *requestHandlerController;
    TSConsole *consoleInstance = nullptr;

signals:
    void signalWithPrint(QString str, PrintType printTyle = printStdout);
};

#endif // TSNETWORK_H
