#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <QDataStream>
#include <QDebug>

class ServerLogic : public QTcpServer
{
    Q_OBJECT


public:
    //explicit ServerLogic(QObject *parent = nullptr);
    ServerLogic();
    bool sconnect();
    QString getIp();


    bool SetPort(long p);
    long getPort();
    void startServer();
    void sendToClient(const QString& got);

signals:
    void receivedText(const QString& s);

private:
    QTcpSocket *ssocket;
    QTcpSocket *rsocket;
    QTcpServer *server;
    long port;

    QByteArray data;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();


};

#endif // SERVERLOGIC_H
