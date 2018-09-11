#ifndef TSCONSOLE_H
#define TSCONSOLE_H

#include <QTextEdit>

// 颜色结构体
struct Color {
    QString kGreen;
    QString kRed;
    QString kPurple;
    QString kOrange;
    QString kBlue;
    QString kBlack;
};

class TSConsole : public QTextEdit
{
    Q_OBJECT
public:
    explicit TSConsole(QWidget *parent = nullptr);

private:
    // 预处理控制台字体颜色
    QString prehandlerColorContent(QString content);
    Color colorUsing = {"#148F77","#FF3C33","#8E44AD",
                        "#CA6F1E","#2874A6","#17202A"};

public slots:
    // 用来展示日志
    void showToConsole(QString content);
};

#endif // TSCONSOLE_H
