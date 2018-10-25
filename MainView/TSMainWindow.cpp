#include <QThread>
#include <QDebug>
#include <QMouseEvent>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QSettings>
#include <QCoreApplication>

#include "TSMainWindow.h"
#include "Tools/TSSqlConnection.h"
#include "Tools/TSConfigUtil.h"
#include "Controllers/TSServerController.h"
#include "Model/TSGlobalAttribute.h"


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

    connect(ui->ts_tabWidget, &QTabWidget::tabBarDoubleClicked, [&](int index){
        qDebug() << "tabBarDoubleClicked: " << index;
        if (index == 1) ui->ts_bodyEditWidget->reloadDataModel();
    });
}


void TSMainWindow::initialTimer() {
    statusTimer = new QTimer(this);
    statusTimer->setInterval(500);
    connect(statusTimer, &QTimer::timeout, [&](){
        // 数组循环换色:
        if (cur_color_index == statuColorSheets.count()-1) cur_color_index=0;
        ui->ts_connectionInfoLabel->setStyleSheet(statuColorSheets.at(cur_color_index));
        cur_color_index++;
    });
}


void TSMainWindow::showEvent(QShowEvent *event)
{
    // 定时器预先设置：
    ui->ts_connectionInfoLabel->setStyleSheet("QLabel {background-color:rgb(112,128,144);}");
    initialTimer();

    connect(ui->ts_startListen, &QPushButton::clicked, [&](){
        printToConsole("+开启服务监听！");
        startServerListen();
        if (!statusTimer->isActive()) statusTimer->start();
    });

    connect(ui->ts_suspendListen, &QPushButton::clicked, [&](){
        printToConsole("+暂停服务监听！");
        if (isServerListening && serverListener != nullptr) serverListener->close();
        ui->ts_connectionInfoLabel->setText("Non-listening");
        ui->ts_connectionInfoLabel->setStyleSheet("QLabel {background-color:rgb(112,128,144);}");
        isServerListening = false;
        if (statusTimer->isActive()) statusTimer->stop();
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

        // 连接控制台信号:
        connect(requestHandlerController, &TSServerController::signal_connectionInfoToConsole,
                ui->ts_consoleWidget, &TSConsole::showToConsole);
    }
    ui->ts_connectionInfoLabel->setText(QString("%1:%2").arg(currentIp()).arg(GlobalStaticPro::serverPort));
    isServerListening = true;
}

QString TSMainWindow::currentIp()
{
    QString t_ip;
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    foreach (QHostAddress ipItem, addresses) {
        if ((ipItem.protocol() == QAbstractSocket::IPv4Protocol)
                &&  (ipItem != QHostAddress::Null)
                && (ipItem != QHostAddress::LocalHost)
                && (ipItem.toString().left(8) == "192.168.")) {
            qDebug() << "Finded-ip: " << ipItem.toString();
            t_ip += "["+ipItem.toString()+"]";
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
}
