#include "serverlogic.h"

ServerLogic::ServerLogic(QObject *parent)
    : QObject{parent}
{
    ssocket = new QTcpSocket(this);
}

void ServerLogic::connect(){
    ssocket->connectToHost("mirea.ru", 80); //Подключаемся к сайту МИРЭА
}

void ServerLogic::getIp(){

}
