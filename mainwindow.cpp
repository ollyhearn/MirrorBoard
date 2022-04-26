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
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Text Over Network!");
    ServerLogic *sl = new ServerLogic();
    sl->connect();
}

//На проект затрачено: 4 ч.

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





void MainWindow::on_actionAbout_triggered()
{
    QMessageBox about;
    about.setTextFormat(Qt::RichText);
    about.setWindowTitle("About ToN");
    about.setText("Simple app to send and receive text over TCP/IP connection!<br><br>by ákd.<br><a href='https://github.com/ollyhearn/'>My GitHub!</a><br><br>v0.0.3");
    about.exec();
}


void MainWindow::on_actionSet_port_triggered()
{
    //srand (time(NULL));
    QString curport = QString::number(sl.getPort());
    while(!sl.SetPort(QInputDialog::getText(this, "Set port", "You can pick any port you wish, uless it is a reserved port", QLineEdit::Normal, curport).toLong())){
        QMessageBox::warning(this, "Scary warning!", "You set the wrong port, use ports only in [1:65535]");
    }
    QMessageBox::information(this, "Congratulations!", "Port set succsess!");

//    if(sl.SetPort(QInputDialog::getText(this, "Set port", "You can pick any port you wish, uless it is a reserved port", QLineEdit::Normal, curport).toLong())){
//        QMessageBox::information(this, "Congratulations!", "Port set succsess!");
//    }
//    else{
//        QMessageBox::warning(this, "Scary warning!", "You set the wrong port, use ports only in [1:65535]");
//    }
}

