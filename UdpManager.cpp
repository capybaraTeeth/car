#include "UdpManager.h"
#include "CarConfig.h"
#include <QJsonDocument>
#include <QDebug>

UdpManager::UdpManager()
{
    //创建套接字对象 （析构中 进行释放）
    socket = new QUdpSocket();

}

UdpManager::UdpManager(const UdpManager &)
{

}

UdpManager &UdpManager::getUdp()
{
    static UdpManager m_udp;
    return m_udp;
}

void UdpManager::setServerInfo(QString ip, quint16 port)
{
    this->serverIp = ip;
    this->serverPort = port;
}

void UdpManager::sendUdpJsonData()
{

    QJsonObject obj = CarConfig::getConfig().buildJsonObject();


    QJsonDocument doc(obj);
    QByteArray arr = doc.toJson(QJsonDocument::Compact);


    socket->writeDatagram(arr,QHostAddress(serverIp) , serverPort);

    qDebug()<<"udp发给服务器的json字符串："<<arr;


}







