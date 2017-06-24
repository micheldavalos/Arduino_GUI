#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "arduino.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Arduino arduino;
    QHash<size_t, QSerialPortInfo> puertos;

    void conectar();
    void desconectar();

public slots:
    void recibirDatos(const QByteArray&datos);
    void enviar();
    void disponibles();

private slots:
    void puertoSeleccionado(int index);
};

#endif // MAINWINDOW_H
