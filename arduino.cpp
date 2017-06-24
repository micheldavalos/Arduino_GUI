#include "arduino.h"

Arduino::Arduino()
{
//    disponibles();
    serial = nullptr;
}


bool Arduino::conectar(size_t indice)
{
    if(serial_disponibles.contains(indice))
        return conectar(serial_disponibles[indice]);
    return false;
}

bool Arduino::conectar(QSerialPortInfo &port)
{

    if(serial == nullptr)
    {
        serial = new QSerialPort(port);
        serial->setBaudRate(baudRate);
        qDebug() << serial->portName() << serial->baudRate() << baudRate;
        bool conexion = serial->open(QIODevice::ReadWrite);
        if(conexion)
        {
            connect(serial, SIGNAL(readyRead()), this, SLOT(lectura()));
            lectura();
            return true;
        }
        else return false;
    }
    else{
        if(serial->isOpen())
        {
            return false;
        }
    }
}

qint32 Arduino::getBaudRate() const
{
    return baudRate;
}

void Arduino::setBaudRate(const qint32 &value)
{
    baudRate = value;
}


bool Arduino::desconectar()
{
    if(serial != nullptr)
    {
        if(serial->isOpen())
        {
            disconnect(serial, SIGNAL(readyRead()), this, SLOT(lectura()));
            serial->close();
            serial->deleteLater();
            serial = nullptr;

            return true;
        }
        serial->deleteLater();
        serial = nullptr;

    }
    else{
        return false;
    }
}

void Arduino::lectura()
{

    qint64 bytes = serial->bytesAvailable();
    if(bytes > 0)
    {
        char *data = new char[bytes];
        serial->read(data, bytes);
        QByteArray data_(data, bytes);
        //    QString texto(data);
        //    QTextStream cout(stdout);

        //    cout << "Respuesta: " << texto << endl;
        emit datos(data_);
    }
}

QHash<size_t, QSerialPortInfo> Arduino::getSerial_disponibles() const
{
    return serial_disponibles;
}

void Arduino::setSerial_disponibles(const QHash<size_t, QSerialPortInfo> &value)
{
    serial_disponibles = value;
}

void Arduino::disponibles()
{
    QSerialPortInfo *seriales = new QSerialPortInfo();
    QList<QSerialPortInfo> seriales_ = seriales->availablePorts();

    serial_disponibles.clear();

    size_t index = 0;

    //    QTextStream cout(stdout);
    foreach (auto l, seriales_) {
#ifdef Q_OS_MACOS
        if( l.portName().contains(QRegExp("^cu.*$")))
#endif
#ifdef Q_OS_WIN
            if( l.portName().contains(QRegExp("^COM.$")))
#endif
            {
                qDebug() << l.portName() << endl;
                serial_disponibles[index++] = l;
            }
    }

//    return serial_disponibles;
}

void Arduino::enviar(const QByteArray &bytes)
{
    if(serial != nullptr && serial->isOpen())
    {
        serial->write(bytes);
    }
    else qDebug() << "Error, no está conectado";
}
