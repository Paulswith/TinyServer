#include <QThread>
#include <QDebug>
#include <QMouseEvent>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QSettings>
#include <QCoreApplication>

#include "TSMainWindow.h"
#include "MainClass/Tools/TSSqlConnection.h"
#include "MainClass/Tools/TSConfigUtil.h"
#include "MainClass/Main/Controller/TSServerController.h"
#include "MainClass/Main/Model/TSGlobalAttribute.h"


TSMainWindow::TSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSMainWindow),
    serverListener(nullptr)
{
    ui->setupUi(this);
    // 设置窗口属性:
    setWindowIcon(QIcon(QPixmap(":/imgs/title.icon")));
    setWindowTitle("Power Tiny-Server");

    connect(this, &TSMainWindow::signal_printToConsole,
            ui->ts_consoleWidget, &TSConsole::showToConsole);
}


void TSMainWindow::initialTimer() {
    statusTimer = new QTimer(this);
    statusTimer->setInterval(500);
    qint8 curIndex = 0;
    connect(statusTimer, &QTimer::timeout, [&](){
        // 数组循环换色:
        curIndex = (curIndex + 1) % statuColorSheets.size();
        ui->ts_connectionInfoLabel->setStyleSheet(statuColorSheets[curIndex]);
    });
}


void TSMainWindow::showEvent(QShowEvent *event)
{
    // 定时器预先设置：
    ui->ts_connectionInfoLabel->setStyleSheet("QLabel {background-color:rgb(112,128,144);}");
    initialTimer();
    connect(ui->ts_startListen, &QPushButton::clicked, [&](){
        signal_printToConsole("+开启服务监听！");
        startServerListen();
        if (!statusTimer->isActive()) statusTimer->start();
    });
    connect(ui->ts_suspendListen, &QPushButton::clicked, [&](){
        signal_printToConsole("+暂停服务监听！");
        if (serverListener->isListening() && serverListener != nullptr) serverListener->close();
        ui->ts_connectionInfoLabel->setText("Non-listening");
        ui->ts_connectionInfoLabel->setStyleSheet("QLabel {background-color:rgb(112,128,144);}");
        if (statusTimer->isActive()) statusTimer->stop();
    });
    event->accept();
}

void TSMainWindow::startServerListen()
{
    if (serverListener != nullptr && serverListener->isListening()) {
        signal_printToConsole("server already listening");
        return;
    }
    auto configPath  = TSConfigUtil::getConfigPath();
    if (configPath.isEmpty()) {
        signal_printToConsole("config file unfind!");
        return;
    }
    QSettings *listenerSettings = new QSettings(configPath, QSettings::IniFormat);
    listenerSettings->beginGroup("listener");
    qDebug() << "Config loaded finished";
    TSServerController *requestHandlerController = new TSServerController();
    serverListener = new stefanfrings::HttpListener(listenerSettings, requestHandlerController, this);
    listenerSettings->endGroup();
    qDebug() << "server init listening";
    // 连接控制台信号:
    connect(requestHandlerController, &TSServerController::signal_connectionInfoToConsole,
            ui->ts_consoleWidget, &TSConsole::showToConsole);
    ui->ts_connectionInfoLabel->setText(QString("0.0.0.0:%1").arg(serverListener->serverPort()));
}

void TSMainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "all-Windows-close";
    try {
        // 关闭数据库连接
        TSSqlConnection::closeSqlConnection();
        // 关闭服务器
        if (serverListener!=nullptr && serverListener->isListening()) serverListener->close();
    } catch (...) {}
    event->accept();
}

TSMainWindow::~TSMainWindow()
{
    delete ui;
    delete statusTimer;
}
