#include "controles.h"
#include "ui_controles.h"
#include <QLayout>

Controles::Controles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controles)
{
    ui->setupUi(this);
    servo = new Servo(this);
    servo2 = new Servo(this);
    servo2->setGeometry(100,100,80,80);
//    ui->centralwidget->layout()->addWidget(&servo);
}

Controles::~Controles()
{
    delete ui;
}
