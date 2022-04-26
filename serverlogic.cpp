#include "serverlogic.h"

ServerLogic::ServerLogic(QObject *parent)
    : QObject{parent}
{
    ssocket = new QTcpSocket(this);
}

bool ServerLogic::connect(){
    ssocket->connectToHost("mirea.ru", 80); //Подключаемся к сайту МИРЭА
    if( ssocket->waitForConnected(1000)){
        return true;
    }
    else return false;
}

QString ServerLogic::getIp(){
    if (connect()){
        return ssocket->localAddress().toString();
    }
    else return "Failed to connect!";
}
