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

        auto validResults = checkSaveData();
        if (validResults.first == validBodyEnum::NoError){
            if (TSSqlConnection::insertBodyData(validResults.second)) {
                qDebug() << "Insert data suc: " << validResults.second;
            }
            QMessageBox::information(this, QString("Bubbling!"),
                                  QString("successfully added!"), QMessageBox::Ok);
            // 更新一下paths
            TSSqlConnection::updateExistPaths();
            emit signal_addNewBody();
        }else{
            QString errorTips;
            switch (validResults.first) {
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
            qDebug() << validResults.first <<" " << validResults.second;
            QMessageBox::critical(this, QString("Identify input error!"),
                                  errorTips, QMessageBox::Discard);
        }
    });
    event->accept();
}

void TSBodyEditWidget::closeEvent(QCloseEvent *event)
{
    emit signal_windowClose();
    event->accept();
}

QPair<validBodyEnum, QStringList> TSBodyEditWidget::checkSaveData()
{
    QStringList insertStrs;
    // 1.检查路径是否存在 & 不为空
    QString path = ui->ts_pathEdit->text();
    if (path.isEmpty() || TSHelpTools::isPathAlreadyExist(path)) return qMakePair(validBodyEnum::pathExistError,insertStrs);

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



TSBodyEditWidget::~TSBodyEditWidget()
{
    delete ui;
}
