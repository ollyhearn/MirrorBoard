#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientlogic.h"
#include "serverlogic.h"

#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtNetwork/QHostAddress>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Text Over Network!");
    ServerLogic *sl = new ServerLogic();
    sl->connect();
}

MainWindow::~MainWindow()
{
    delete ui;

}

//QString MainWindow::getIp(){
//    if (this->ip->waitForConnected(30)) {
//        QString adress = 0;//this->ip->QTcpSocket::localAddress().toString();
//        return "Your IP adress: " + adress;
//    } else {
//        return "Error retreiving IP adress";
//    }
//}

void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
}


void MainWindow::on_clientRadio_clicked()
{
    ui->clientRadio->setChecked(true);
    checkRadio();
}


void MainWindow::on_serverRadio_clicked()
{
    ui->serverRadio->setChecked(true);
    checkRadio();
}

void MainWindow::checkRadio(){
    if (ui->clientRadio->isChecked()){
        ui->ipText->setPlaceholderText("Enter server IP here..");
        ui->ipText->setEnabled(true);
        ui->textEdit->clear();
        ui->textEdit->setEnabled(true);
        ui->textEdit->setPlaceholderText("Send text to server! Type something and click \"Submit!\"");


    }
    else if (ui->serverRadio->isChecked()){
        ui->ipText->setEnabled(false);
        ui->ipText->clear();
        ui->ipText->setPlaceholderText(sl.getIp());
        ui->textEdit->setEnabled(false);
        ui->textEdit->setPlaceholderText("You will receive message here!");
        //QTcpSocket socket;


    }
    else {
        ui->textEdit->setText("Error");
    }
}



void MainWindow::on_submitButton_clicked()
{

}

