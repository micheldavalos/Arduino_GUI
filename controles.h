#ifndef CONTROLES_H
#define CONTROLES_H

#include <QMainWindow>
#include "servo.h"

namespace Ui {
class Controles;
}

class Controles : public QMainWindow
{
    Q_OBJECT

public:
    explicit Controles(QWidget *parent = 0);
    ~Controles();

private:
    Ui::Controles *ui;
    Servo *servo;
    Servo *servo2;
};

#endif // CONTROLES_H
