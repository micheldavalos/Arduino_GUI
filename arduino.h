#ifndef ARDUINO_H
#define ARDUINO_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QHash>
#include <QTextStream>
#include <QDebug>

class Arduino : public QObject
{
    Q_OBJECT
private:
    QSerialPort *serial;
    QHash<size_t, QSerialPortInfo> serial_disponibles;

    bool conectar(QSerialPortInfo &port);
    void run();
    qint32 baudRate;
public:
    explicit Arduino();
    bool conectar(size_t indice);
    bool desconectar();
    const QHash<size_t, QSerialPortInfo> &disponibles();
    void enviar(const QByteArray &bytes);

    qint32 getBaudRate() const;
    void setBaudRate(const qint32 &value);

signals:
    void datos(QByteArray);

public slots:
    void lectura();
};

#endif // ARDUINO_H
