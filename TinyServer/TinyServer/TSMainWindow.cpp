#include "TSMainWindow.h"
#include "ui_TS_design.h"

TSMainWindow::TSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TSMainWindow)
{
    ui->setupUi(this);
}

TSMainWindow::~TSMainWindow()
{
    delete ui;
}
