#include <QThread>
#include <QDebug>
#include <QMouseEvent>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QSettings>

#include "TSMainWindow.h"
#include "Tools/TSSqlConnection.h"
#include "Tools/TSConfigUtil.h"
#include "Controllers/TSServerController.h"
#include "Model/TSGlobalAttribute.h"

TSMainWindow::TSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSMainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    connect(this, &TSMainWindow::signal_printToConsole,
            ui->ts_consoleWidget, &TSConsole::showToConsole);

    connect(ui->ts_tabWidget, &QTabWidget::tabBarDoubleClicked, [&](int index){
        qDebug() << "tabBarDoubleClicked: " << index;
        if (index == 1) ui->ts_bodyEditWidget->reloadDataModel();
    });
}

void TSMainWindow::showEvent(QShowEvent *event)
{
    connect(ui->ts_startListen, &QPushButton::clicked, [&](){
        printToConsole("+请求开启服务监听！");
        startServerListen();
    });

    connect(ui->ts_suspendListen, &QPushButton::clicked, [&](){
        printToConsole("+暂停服务监听！");
        if (serverListener != nullptr) serverListener->close();
        ui->ts_connectionInfoLabel->setText("Non-listening");
    });

    event->accept();
}

void TSMainWindow::startServerListen()
{
    if (serverListener != nullptr) {
        if (serverListener->isListening()) {
            qDebug() << "server already listening";
        }else{
            serverListener->listen();
            qDebug() << "server restart listening";
        }
    }else{
        auto configPath  = TSConfigUtil::getConfigPath();
        if (configPath.isEmpty()) {
            qDebug() << "config file unfind!";
            return;
        }
        QSettings *listenerSettings =
                    new QSettings(configPath, QSettings::IniFormat);
        listenerSettings->beginGroup("listener");
        qDebug() << "Config loaded finished";

        TSServerController *requestHandlerController = new TSServerController();
        serverListener = new stefanfrings::HttpListener(listenerSettings, requestHandlerController, this);
        qDebug() << "server init listening";

//        // 连接控制台信号:
//        connect(requestHandlerController, &TSServerController::signal_onnectionInfoToConsole, [&](QString infoContent){
//            printToConsole(infoContent);
//        });
    }
    ui->ts_connectionInfoLabel->setText(QString("%1:%2").arg(currentIp()).arg(GlobalStaticPro::serverPort));
}

QString TSMainWindow::currentIp()
{
    QString t_ip;
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    foreach (QHostAddress ipItem, addresses) {
        if ((ipItem.protocol() == QAbstractSocket::IPv4Protocol)
                &&  (ipItem != QHostAddress::Null)
                && (ipItem != QHostAddress::LocalHost)
                && (ipItem.toString().left(3) == "192")) {
            qDebug() << "Finded-ip: " << ipItem.toString();
            t_ip = ipItem.toString();
        }
    }
    return t_ip;
}

void TSMainWindow::printToConsole(QString str)
{
    emit signal_printToConsole(str);
}

void TSMainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "all-Windows-close";
    if (bodyEditWidget != nullptr) bodyEditWidget->close(); // 要关一起关
    TSSqlConnection::closeSqlConnection();  // 关闭数据库连接
    event->accept();
}

TSMainWindow::~TSMainWindow()
{
    delete ui;
}
