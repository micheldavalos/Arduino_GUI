#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

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
    connect(ui->pushButton, SIGNAL(clicked(bool)), ui->plainTextEditRespuesta, SLOT(clear()));

    ui->botonEnviar->setEnabled(false);
    ui->pushButtonConectar->setEnabled(false);
    ui->pushButtonDesconectar->setEnabled(false);

    actualizaPuertos();

    labelBaudrate = labelConectado = nullptr;

//    connect(ui->horizontalSlider_blue, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_valueChanged(int)));
    connect(ui->horizontalSlider_green, SIGNAL(valueChanged(int)), this, SLOT(on_horizontalSlider_valueChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizaPuertos()
{
    ui->comboBox->clear();
    arduino.disponibles();
    puertos = arduino.getSerial_disponibles();

    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);

    for(int i = 0; i < puertos.size(); i++)
    {
        ui->comboBox->insertItem(i, puertos[i].portName());
    }
    ui->comboBox->setCurrentText(puertoActual);
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

        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);

        ui->horizontalSlider_green->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_4->setEnabled(true);

        if( labelConectado == nullptr)
        {
            labelConectado = new QLabel("Conectado: " + ui->comboBox->currentText());
            ui->statusBar->addWidget(labelConectado);
        }
        if( labelBaudrate == nullptr)
        {
            labelBaudrate = new QLabel("Baudrate: " + ui->comboBox_2->currentText());
            ui->statusBar->addWidget(labelBaudrate);
        }
        labelConectado->setText(("Conectado: " + ui->comboBox->currentText()));
        labelBaudrate->setText("Baudrate: " + ui->comboBox_2->currentText());
        labelConectado->show();
        labelBaudrate->show();

        puertoActual = ui->comboBox->currentText();

    }
    else {
        QMessageBox::critical(this, "Advertencia", "Error al conectar");
    }
}

void MainWindow::desconectar()
{
    if( arduino.desconectar() )
    {
        ui->botonEnviar->setEnabled(false);
        ui->pushButtonDesconectar->setEnabled(false);

        ui->horizontalSlider_green->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);


        actualizaPuertos();

//        ui->statusBar->removeWidget(labelConectado);
//        ui->statusBar->removeWidget(labelBaudrate);
        labelConectado->hide();
        labelBaudrate->hide();


    }
}

void MainWindow::recibirDatos(const QByteArray &datos)
{
//    qDebug() << datos;
    ui->plainTextEditRespuesta->insertPlainText(QString(datos));
    ui->plainTextEditRespuesta->centerCursor();
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


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QJsonObject json;
    QString objecto = sender()->objectName();


    if (objecto == "horizontalSlider_green")
        json.insert("tipo", QJsonValue(2));

    json.insert("valor", QJsonValue(value));
//    qDebug() << json;
//    qDebug() << QJsonDocument(json).toJson(QJsonDocument::Compact);

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));

}

void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject json;
    QString objecto = sender()->objectName();

    json.insert("tipo", QJsonValue(1));
    json.insert("valor", 1);

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));

    ui->pushButton_3->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    QJsonObject json;
    QString objecto = sender()->objectName();

    json.insert("tipo", QJsonValue(1));
    json.insert("valor", 0);

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    QJsonObject json;
    QString objecto = sender()->objectName();

    json.insert("tipo", QJsonValue(3));
    json.insert("valor", 1);

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));

    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_5_clicked()
{
    QJsonObject json;
    QString objecto = sender()->objectName();

    json.insert("tipo", QJsonValue(3));
    json.insert("valor", 0);

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));

    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
//    qDebug() << arg1;
}

void MainWindow::on_pushButton_6_clicked()
{
//    qDebug() << ui->spinBox->text().toInt();

    QJsonObject json;
    QString objecto = sender()->objectName();

    json.insert("tipo", QJsonValue(4));
    json.insert("valor", ui->spinBox->text().toInt());

    arduino.enviar(QJsonDocument(json).toJson(QJsonDocument::Compact));
}
