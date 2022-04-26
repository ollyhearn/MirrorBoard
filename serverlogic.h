#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class ServerLogic : public QObject
{
    Q_OBJECT
public:
    explicit ServerLogic(QObject *parent = nullptr);

    void getIp();
    bool connect();
signals:

public slots:
    QTcpSocket *ssocket;

};

#endif // SERVERLOGIC_H
