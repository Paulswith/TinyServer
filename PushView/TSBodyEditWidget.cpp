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
    ui->ts_updateBtn->setEnabled(false);
}

void TSBodyEditWidget::setUpdateBtnEnable(bool shouldEnable)
{
    ui->ts_updateBtn->setEnabled(shouldEnable);
}

void TSBodyEditWidget::showEvent(QShowEvent *event)
{
    // 目前只支持POST,所以暂时锁定了
    ui->ts_methodEdit->setText("POST");
    ui->ts_methodEdit->setEnabled(false);
    // commit:
    connect(ui->ts_commitBtn, &QPushButton::clicked, [&](){
        auto validResults = checkSaveData();
        if (validResults.first != validBodyEnum::NoError){
            showTips(validResults.first);
        }else{
            if (TSSqlConnection::insertBodyData(validResults.second)) {
                qDebug() << "Insert data suc: " << validResults.second;
                QMessageBox::information(this, QString("Bubbling!"),
                                      QString("successfully added!"), QMessageBox::Ok);
            }else{
                QMessageBox::critical(this, QString("Oh-no!"),
                                      QString("insert-data fail!!"), QMessageBox::Close);
            }
            // 更新一下paths
            emit signal_addNewBody();
        }
    });

    // update
    connect(ui->ts_updateBtn, &QPushButton::clicked, [&](){
        auto validResults = checkSaveData(false);
        if (validResults.first != validBodyEnum::NoError){
            showTips(validResults.first);
        }else{
            if (TSSqlConnection::updateBodyDataWithPath(validResults.second)) {
                qDebug() << "Insert data suc: " << validResults.second;
                QMessageBox::information(this, QString("Bubbling!"),
                                      QString("successfully update!"), QMessageBox::Ok);
            }else{
                QMessageBox::critical(this, QString("Oh-no!"),
                                      QString("update-data fail!!"), QMessageBox::Close);
            }
            qDebug() << "need update data:" << validResults.second;
            // 更新一下paths
            emit signal_addNewBody();
        }
    });
    event->accept();
}

void TSBodyEditWidget::showTips(const validBodyEnum &enumError)
{
    QString errorTips;
    switch (enumError) {
    case validBodyEnum::pathExistError:
        errorTips = "requests path already exist.";
        break;
    case validBodyEnum::reqMothodUnMatchError:
        errorTips = "requests method not POST.";
        break;
    case validBodyEnum::reqJsonInvalidError:
        errorTips = "requests body-json invalid.";
        break;
    case validBodyEnum::rspJsonInvalidError:
        errorTips = "response body-json invalid.";
        break;
    default:
        break;
    }
    QMessageBox::critical(this, QString("Identify input error!"),
                          errorTips, QMessageBox::Discard);
}

void TSBodyEditWidget::closeEvent(QCloseEvent *event)
{
    emit signal_windowClose();
    event->accept();
}

QPair<validBodyEnum, QStringList> TSBodyEditWidget::checkSaveData(bool checkPath)
{
    QStringList insertStrs;
    // 1.检查路径是否存在 & 不为空
    QString path = ui->ts_pathEdit->text();
    if (checkPath){
        if (path.isEmpty() || TSHelpTools::isPathAlreadyExist(path)) return qMakePair(validBodyEnum::pathExistError,insertStrs);
    }

    // 2.目前只允许POST
    QString method = ui->ts_methodEdit->text();
    if (method != "POST") return qMakePair(validBodyEnum::reqMothodUnMatchError,insertStrs);

    // 3. Json不能有异常， 允许为空
    QString analyReqJson;
    QString reqText = ui->ts_requestEdit->toPlainText();
    if (TSHelpTools::isInvalidJson(reqText, analyReqJson)) return qMakePair(validBodyEnum::reqJsonInvalidError,insertStrs);

    // 4. 不为空, Json不能有异常
    QString analyRspJson;
    QString rspText = ui->ts_responseEdit->toPlainText();
    if (rspText.isEmpty() || TSHelpTools::isInvalidJson(rspText, analyRspJson)) return qMakePair(validBodyEnum::rspJsonInvalidError,insertStrs);

    insertStrs << path << method << analyReqJson << analyRspJson;

//    bool isEquual = (QJsonDocument::fromJson(reqText.toLatin1()) == QJsonDocument::fromJson(rspText.toLatin1()));
//    qDebug() << "isjson == ? " << isEquual;
    return qMakePair(validBodyEnum::NoError,insertStrs);
}

void TSBodyEditWidget::showViewWindowWithData(const QStringList &data)
{
    ui->ts_pathEdit->setText(data.at(0));
    ui->ts_pathEdit->setEnabled(false);

    ui->ts_methodEdit->setText(data.at(1));
    ui->ts_requestEdit->setText(data.at(2));
    ui->ts_responseEdit->setText(data.at(3));
    ui->ts_commitBtn->setEnabled(false);
}


TSBodyEditWidget::~TSBodyEditWidget()
{
    delete ui;
}
