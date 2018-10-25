#include "TSLCDClock.h"
#include <QDateTime>
#include <QDebug>


// 显示时间的格式
QString const kClockFormat = "MM-dd HH:mm:ss";

TSLCDClock::TSLCDClock(QWidget *parent) : QLCDNumber(parent)
{
    setLCDProperty();
    initialTimer();
}

void TSLCDClock::setLCDProperty()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    display(dateTime.toString(kClockFormat));

    setPalette(Qt::black);
    setDigitCount(14);
    setMode(QLCDNumber::Dec);
    setSegmentStyle(QLCDNumber::Flat);
    setStyleSheet("border: 3px solid green; color: green; background: silver;");
}


void TSLCDClock::initialTimer()
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [&]() {
        QDateTime dateTime = QDateTime::currentDateTime();
//        qDebug() << dateTime << endl;
        display(dateTime.toString(kClockFormat));
    });
    timer->start();
}
