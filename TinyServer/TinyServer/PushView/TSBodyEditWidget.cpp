#include "TSBodyEditWidget.h"
#include "Tools/TSSqlConnection.h"
#include "Tools/TSHelpTools.h"
#include "Model/TSGlobalAttribute.h"

#include <QDebug>
#include <QShowEvent>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QMessageBox>

TSBodyEditWidget::TSBodyEditWidget(QRect geometry, QWidget *parent)
    :QWidget (parent), ui(new Ui::TSBodyEditWidget)
{
    ui->setupUi(this);
    setGeometry(geometry);
}

void TSBodyEditWidget::showEvent(QShowEvent *event)
{

    connect(ui->ts_commitBtn, &QPushButton::clicked, [&](){

        QPair<bool, QStringList> validResults = checkSaveData();
        if (validResults.first){
            if (TSSqlConnection::insertBodyData(validResults.second)) {
                qDebug() << "Insert data suc: " << validResults.second;
            }
            QMessageBox::information(this, QString("Bubbling!"),
                                  QString("successfully added!"), QMessageBox::Ok);
            // 更新一下paths
            TSSqlConnection::updateExistPaths();
            emit signal_addNewBody();
        }else{
            qDebug() << validResults.first <<" " << validResults.second;
            QMessageBox::critical(this, QString("Identify input error!"),
                                  QString("Please check what you input."), QMessageBox::Ok);
        }
    });
    event->accept();
}

void TSBodyEditWidget::closeEvent(QCloseEvent *event)
{
    emit signal_windowClose();
    event->accept();
}

QPair<bool, QStringList> TSBodyEditWidget::checkSaveData()
{
    QStringList insertStrs;
    // 1.检查路径是否存在 & 不为空
    QString path = ui->ts_pathEdit->text();
    if (path.isEmpty() || TSHelpTools::isPathAlreadyExist(path)) return qMakePair(false,insertStrs);

    // 2.目前只允许POST
    QString method = ui->ts_methodEdit->text();
    if (method != "POST") return qMakePair(false,insertStrs);

    // 3. Json不能有异常， 允许为空
    QString reqText = ui->ts_requestEdit->toPlainText();
    if (TSHelpTools::isInvalidJson(reqText)) return qMakePair(false,insertStrs);

    // 4. 不为空, Json不能有异常
    QString rspText = ui->ts_responseEdit->toPlainText();
    if (rspText.isEmpty() || TSHelpTools::isInvalidJson(rspText)) return qMakePair(false,insertStrs);

    insertStrs << path << method << reqText << rspText;
    return qMakePair(true,insertStrs);
}



TSBodyEditWidget::~TSBodyEditWidget()
{
    delete ui;
}
