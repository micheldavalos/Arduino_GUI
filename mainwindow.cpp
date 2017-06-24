#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->botonEnviar, SIGNAL(clicked(bool)), this, SLOT(enviar()));
    connect(&arduino, SIGNAL(datos(QByteArray)), this, SLOT(recibirDatos(QByteArray)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(puertoSeleccionado(int)));
    connect(ui->pushButtonConectar, SIGNAL(clicked(bool)), this, SLOT(conectar()));
    connect(ui->pushButtonDesconectar, SIGNAL(clicked(bool)), this, SLOT(desconectar()));

    ui->botonEnviar->setEnabled(false);
    ui->pushButtonConectar->setEnabled(false);
    ui->pushButtonDesconectar->setEnabled(false);

    actualizaPuertos();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizaPuertos()
{
    arduino.disponibles();
    ui->comboBox->clear();
    puertos = arduino.getSerial_disponibles();

    for(int i = 0; i < puertos.size(); i++)
    {
        ui->comboBox->insertItem(i, puertos[i].portName());
    }
}

void MainWindow::conectar()
{
//    qDebug() << "conectar";

    bool ok;
    arduino.setBaudRate(ui->comboBox_2->currentText().toInt(&ok));

    if( arduino.conectar(ui->comboBox->currentIndex()) ) // modificar para que envie el puerto seleccionado
    {
        ui->botonEnviar->setEnabled(true);
        ui->pushButtonConectar->setEnabled(false);
        ui->pushButtonDesconectar->setEnabled(true);
    }
}

void MainWindow::desconectar()
{
    if( arduino.desconectar() )
    {
        ui->botonEnviar->setEnabled(false);
        ui->pushButtonDesconectar->setEnabled(false);

        actualizaPuertos();
    }
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

void MainWindow::puertoSeleccionado(int index)
{
    ui->comboBox_2->clear();
    ui->comboBox->itemText(index);

    int posicion = -1;
    int valor;
    foreach(auto e, puertos[index].standardBaudRates())
    {
        ui->comboBox_2->addItem(QString::number(e));
        posicion++;
        if(e == 9600)
            valor = posicion;

    }

    if( posicion > -1){
        ui->comboBox_2->setCurrentIndex(valor);
        ui->pushButtonConectar->setEnabled(true);
    }
}
