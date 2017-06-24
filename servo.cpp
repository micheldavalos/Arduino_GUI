#include "servo.h"
#include "QLayout"
#include <QDebug>

Servo::Servo(QWidget *parent) : QWidget(parent)
{
//    QLayout *layout = this->layout();
    QGridLayout *layout = new QGridLayout(this);

    if(layout == nullptr)
        qDebug()<< "nulo layout";
    this->setGeometry(0,0,200,200);
    dial.setGeometry(0,0,81,81);
    dial.setMaximum(200);
    dial.setMinimum(50);

    layout->addWidget(&dial);
}
