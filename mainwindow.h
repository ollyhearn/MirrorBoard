#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serverlogic.h"

#include <QMainWindow>
#include <QtNetwork/QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();

    void on_clientRadio_clicked();

    void on_serverRadio_clicked();

    void on_submitButton_clicked();

    void checkRadio();

private:
    Ui::MainWindow *ui;
    ServerLogic sl;
};
#endif // MAINWINDOW_H
