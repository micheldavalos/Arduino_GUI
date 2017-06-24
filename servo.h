#ifndef SERVO_H
#define SERVO_H

#include <QWidget>
#include <QDial>

class Servo : public QWidget
{
    Q_OBJECT
public:
    explicit Servo(QWidget *parent = nullptr);

private:
    QDial dial;

signals:

public slots:
};

#endif // SERVO_H
