#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->botonEnviar, SIGNAL(clicked(bool)), this, SLOT(enviar()));
    connect(&arduino, SIGNAL(datos(QByteArray)), this, SLOT(recibirDatos(QByteArray)));

//    conectar();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conectar()
{
//    qDebug() << "conectar";
    arduino.conectar(1);
}

void MainWindow::desconectar()
{
    arduino.desconectar();
}

void MainWindow::recibirDatos(const QByteArray &datos)
{
//    qDebug() << datos;
    ui->plainTextEditRespuesta->insertPlainText(QString(datos));
}

void MainWindow::enviar()
{
    QString text = ui->lineEditEnviar->text();
   if(!text.isEmpty())
   {
       QByteArray datos = text.toLatin1();
       arduino.enviar(datos);
       ui->lineEditEnviar->clear();
   }
   else{
       QMessageBox msgBox;
       msgBox.setText("No se envió nada porque está vacío");
       msgBox.exec();
   }
}

void MainWindow::disponibles()
{
//    ui->menuPuertos->addAction("COM1");
    qDebug() << "aqui";
}
