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

    ui->pushButtonConectar->setEnabled(false);
    ui->pushButtonDesconectar->setEnabled(false);
//    conectar();
    puertos = arduino.disponibles();

    foreach(auto puerto, puertos)
    {
        ui->comboBox->addItem(puerto.portName());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conectar()
{
    qDebug() << "conectar";
    if( arduino.conectar(1) )
    {
        ui->pushButtonConectar->setEnabled(false);
        ui->pushButtonDesconectar->setEnabled(true);
    }
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
