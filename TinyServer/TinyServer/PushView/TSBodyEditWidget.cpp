#include "TSBodyEditWidget.h"
#include "ui_TSBodyEdit_design.h"

TSBodyEditWidget::TSBodyEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TSBodyEditWidget)
{
    ui->setupUi(this);
}

TSBodyEditWidget::TSBodyEditWidget(QRect geometry, QWidget *parent)
    :QWidget (parent), ui(new Ui::TSBodyEditWidget)
{
    ui->setupUi(this);
    setGeometry(geometry);
}

TSBodyEditWidget::~TSBodyEditWidget()
{
    delete ui;
}
