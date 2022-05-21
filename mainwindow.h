#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serverlogic.h"
#include "clientlogic.h"

#include <QMainWindow>
#include <clientlogic.h>
#include <QtNetwork/QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void on_clearButton_clicked();

    void on_clientRadio_clicked();

    void on_serverRadio_clicked();

    void on_submitButton_clicked();

    void checkRadio();

    void on_actionAbout_triggered();

    void on_actionSet_port_triggered();

    void on_connectButton_clicked();

    void on_copyButton_clicked();
    void on_textEdit_textChanged();

public slots:
    void replaceText(const QString& s);
private:
    Ui::MainWindow *ui;
    ServerLogic *sl;
    ClientLogic *cl;
    QClipboard *Clipboard;
    int copyCount = 1;
    int strlength = 0;
};
#endif // MAINWINDOW_H
