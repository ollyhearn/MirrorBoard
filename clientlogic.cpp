#include "clientlogic.h"
#include "serverlogic.h"

ClientLogic::ClientLogic(QObject *parent)
    : QObject{parent}
{
    //connect(csocket, &QTcpSocket::readyRead, this, &ClientLogic::slotReadyRead);
    //connect(csocket, &QTcpSocket::disconnected, csocket, &QTcpSocket::deleteLater);
}

void ClientLogic::slotReadyRead()
{

}

bool ClientLogic::clientConnect(QString ip){
    QStringList i = ip.split(":");
    return true;
}
