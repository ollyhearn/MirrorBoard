#ifndef CLIENTLOGIC_H
#define CLIENTLOGIC_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <QDebug>

class ClientLogic : public QTcpSocket
{
    Q_OBJECT
public:
    ClientLogic();

    bool clientConnect(QString ip);

    void SendToServer(QString str);
    void SendMessage(QString input);
private:
    QTcpSocket *csocket;
    QByteArray data;

signals:

public slots:
    void slotReadyRead();

};

#endif // CLIENTLOGIC_H
