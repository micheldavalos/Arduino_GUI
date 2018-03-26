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

    void actualizaPuertos();

    QLabel *labelConectado;
    QLabel *labelBaudrate;
    QString puertoActual;


public slots:
    void recibirDatos(const QByteArray&datos);
    void enviar();
    void disponibles();

private slots:
    void conectar();
    void puertoSeleccionado(int index);
    void desconectar();

    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_spinBox_valueChanged(int arg1);
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
};

#endif // MAINWINDOW_H

