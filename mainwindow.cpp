#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->botonEnviar, SIGNAL(clicked(bool)), this, SLOT(enviar()));
    connect(&arduino, SIGNAL(datos(QByteArray)), this, SLOT(recibirDatos(QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recibirDatos(const QByteArray &datos)
{
    qDebug() << datos;
}

void MainWindow::enviar()
{
    qDebug() << "click";
}
