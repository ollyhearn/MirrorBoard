#include "mainwindow.h"
#include "qclipboard.h"
#include "ui_mainwindow.h"
#include "clientlogic.h"
#include "serverlogic.h"

#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QStatusBar>

#include <QTcpSocket>
#include <QTcpServer>

#include <QString>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), sl(new ServerLogic()), cl(new ClientLogic())
{

    ui->setupUi(this);
    setWindowTitle("MirrorBoard");
    setWindowIcon(QIcon(":/res/icons/m512.png"));
    ui->ipText->setPlaceholderText("Enter server IP:Port here..");
    ui->statusbar->setStyleSheet("color: #9e2601");
    ui->statusbar->showMessage("Not connected!");
    ui->copyButton->setEnabled(false);

    sl->sconnect();
    //connect(rsocket, &QTcpSocket::disconnected, this, &ServerLogic::deleteLater);
    connect(sl, &ServerLogic::receivedText, this, &MainWindow::replaceText);

}

//На проект затрачено: 12 ч.

MainWindow::~MainWindow()
{
    delete sl;
    delete cl;
    delete ui;

}

void MainWindow::on_clearButton_clicked()
{
    ui->textEdit->clear();
    cl->SendMessage("CLEAR");
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
        ui->ipText->setPlaceholderText("Enter server IP:Port here..");
        ui->ipText->setEnabled(true);
        ui->ipText->clear();
        ui->connectButton->setEnabled(true);
        ui->submitButton->setEnabled(true);
        ui->copyButton->setEnabled(false);
        ui->copyButton->setText("Copy");
        copyCount = 1;
        ui->textEdit->clear();
        //ui->textEdit->setEnabled(true);
        //ui->textEdit->setPlaceholderText("Send text to server! Type something and click \"Submit!\"");


    }
    else if (ui->serverRadio->isChecked()){
        ui->ipText->setEnabled(false);
        ui->connectButton->setEnabled(false);
        ui->submitButton->setEnabled(false);
        ui->ipText->clear();
        ui->copyButton->setText("Copy");
        ui->copyButton->setEnabled(true);
        copyCount = 1;
        qDebug() << "Server starting";
        sl->startServer();
        ui->ipText->setText(sl->getIp() + ":" + QString::number(sl->getPort()));
        //ui->textEdit->setEnabled(false);
        //ui->textEdit->setPlaceholderText("You will receive message here!");


    }
    else {
        ui->textEdit->setText("Error");
    }
}



void MainWindow::on_submitButton_clicked()
{
    cl->SendMessage(ui->textEdit->toPlainText());
}

void MainWindow::on_textEdit_textChanged()
{
    const QString& s = ui->textEdit->toPlainText();
    if(ui->clientRadio->isChecked()){
        if(s.length() != strlength + 1){
            cl->SendMessage("BACKSPACE");
        }
        else{
            cl->SendMessage(s[s.length()-1]);
        }
    }
    else{
        if(s.length() != strlength + 1){
            sl->sendToClient("BACKSPACE");
        }
        else{
            sl->sendToClient(s[s.length()-1]);
        }
    }

    strlength = s.length();
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox about;
    about.setTextFormat(Qt::RichText);
    about.setWindowTitle("About MirrorBoard");
    about.setText("Simple app to mirror your text over TCP/IP connection!<br><br>by ákd.<br><a href='https://github.com/ollyhearn/'>My GitHub!</a><br><br>v2.0.1");
    about.exec();
}


void MainWindow::on_actionSet_port_triggered()
{
    QString curport = QString::number(sl->getPort());
    while(!sl->SetPort(QInputDialog::getText(this, "Set port", "You can pick any port you wish, uless it is a reserved port", QLineEdit::Normal, curport).toLong())){
        QMessageBox::warning(this, "Scary warning!", "You set the wrong port, use ports only in [1:65535]");
    }
    checkRadio();
    QMessageBox::information(this, "Congratulations!", "Port set succsess!");
}


void MainWindow::on_connectButton_clicked()
{
    if(cl->clientConnect(ui->ipText->toPlainText())){
        ui->statusbar->setStyleSheet("color: #298244");
        ui->statusbar->showMessage("Connected!");
    }
    else{
        ui->statusbar->setStyleSheet("color: #9e2601");
        ui->statusbar->showMessage("Wrong IP:Port!", 2000);
    }
}


void MainWindow::on_copyButton_clicked()
{
    Clipboard->setText(ui->ipText->toPlainText());
    if(copyCount == 1){
        ui->copyButton->setText("Copied!");
    }
    else{
        if(copyCount < 10){
            ui->copyButton->setText("Copied x" + QString::number(copyCount) + "!");
        }
        else{
            ui->copyButton->setText(":(");
            ui->copyButton->setDisabled(true);
            QMessageBox::information(this, "you shit", "stop doing this");
        }
    }
    ++copyCount;
}

void MainWindow::replaceText(const QString& s){
    ui->statusbar->setStyleSheet("color: #303aad");
    ui->statusbar->showMessage("Receiving...", 2000);
    if (s == "BACKSPACE" || s == "CLEAR"){
        QString ct = ui->textEdit->toPlainText();
        if (s == "BACKSPACE"){
            ct.chop(1);
            ui->textEdit->setText(ct);
        }
        if (s == "CLEAR"){
            ui->textEdit->setText("");
        }
    }
    else{
        ui->textEdit->setText(ui->textEdit->toPlainText()+s);
    }
}



