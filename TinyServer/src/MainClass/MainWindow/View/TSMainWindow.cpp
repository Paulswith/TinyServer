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
#include "MainClass/Tools/TSConfigUtil.hpp"
#include "MainClass/MainWindow/Controller/TSServerController.h"


const QString kDisconnectStatusStyleSheet = "QLabel {background-color:rgb(80, 88, 105);}";
const QString kDisconnectStatusText = "non-listen";
const QString kConnectedStatusStyleSheet = "QLabel {background-color:rgb(80, 250, 123);}";


TSMainWindow::TSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSMainWindow)
{
    ui->setupUi(this);
}

/* ~~~~~~~~~~~~~~~~~~~~~events~~~~~~~~~~~~~~~~~~~~~ */
void TSMainWindow::showEvent(QShowEvent *event)
{
    network = new TSNetWork(ui->ts_consoleWidget);
    connectAllSignals();
    setupWidget();
    event->accept();
}

void TSMainWindow::closeEvent(QCloseEvent *event)
{
    try {
        // 关闭数据库连接
        TSSqlConnection::closeSqlConnection();
    } catch (...) {}
    event->accept();
}

/* ~~~~~~~~~~~~~~~~~ui-handle~~~~~~~~~~~~~~~~~ */
void TSMainWindow::setupWidget()
{
    setWindowIcon(QIcon(QPixmap(":/imgs/title.icon")));
    setWindowTitle("Power Tiny-Server");
    initialTimer();
    ui->ts_connectionInfoLabel->setStyleSheet(kDisconnectStatusStyleSheet);
    ui->ts_startListen->setEnabled(true);
    ui->ts_suspendListen->setEnabled(false);
}
void TSMainWindow::initialTimer() {
    statusTimer = new QTimer(this);
    statusTimer->setInterval(500);
    connect(statusTimer, &QTimer::timeout, [&](){
        // 数组循环换色:
        timerCurrentIndex = (timerCurrentIndex + 1) % statuColorSheets.size();
        ui->ts_connectionInfoLabel->setStyleSheet(statuColorSheets[timerCurrentIndex]);
    });
}

/* ~~~~~~~~~~~~~~~~~signal handling ~~~~~~~~~~~~~~~~~*/
void TSMainWindow::connectAllSignals()
{
    connect(this, &TSMainWindow::signalWithPrintToConsole,
            ui->ts_consoleWidget, &TSConsole::slotWithprint);
    connect(network, &TSNetWork::signalWithPrint,
            ui->ts_consoleWidget, &TSConsole::slotWithprint);
    //
    connect(ui->ts_startListen, &QPushButton::clicked,
            this, &TSMainWindow::startServerListen);
    connect(ui->ts_suspendListen, &QPushButton::clicked,
            this, &TSMainWindow::suspendServerListen);
}

/* ~~~~~~~~~~~~~~~~~~server handling ~~~~~~~~~~~~~~~~~~*/
void TSMainWindow::startServerListen()
{
    QString errMsg;
    bool startStatus = network->startServerListenWithConfig(TSConfigUtil::getConfigPath(), errMsg);
    if (!startStatus) {
        signalWithPrintToConsole(errMsg, PrintType::printStderr);
        return;
    }
    auto text = QString("0.0.0.0:%1").arg(network->getListenPort());
    ui->ts_connectionInfoLabel->setText(text);
    ui->ts_connectionInfoLabel->setStyleSheet(kConnectedStatusStyleSheet);
    signalWithPrintToConsole("-- Started Server listen succeed", PrintType::printStdsuc);
    // 启动状态器
    if (!statusTimer->isActive()) statusTimer->start();
    ui->ts_startListen->setEnabled(false);
    ui->ts_suspendListen->setEnabled(true);
}
void TSMainWindow::suspendServerListen()
{
    network->suspendServerListen();
    ui->ts_connectionInfoLabel->setText(kDisconnectStatusText);
    ui->ts_connectionInfoLabel->setStyleSheet(kDisconnectStatusStyleSheet);
    if (statusTimer->isActive()) statusTimer->stop();
    signalWithPrintToConsole("-- Supend server listen");
    ui->ts_startListen->setEnabled(true);
    ui->ts_suspendListen->setEnabled(false);
}

TSMainWindow::~TSMainWindow()
{
    if (nullptr != ui) delete ui;
    if (nullptr != statusTimer) delete statusTimer;
    if (nullptr != network) delete network;
}
