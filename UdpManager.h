#ifndef UDPMANAGER_H
#define UDPMANAGER_H

#include <QString>
#include <QUdpSocket>
#include <QJsonDocument>


class UdpManager
{
    UdpManager();
    UdpManager(const UdpManager&);
    //套接字
    QUdpSocket* socket;
    //服务器ip
    QString serverIp;
    //服务器端口
    quint16 serverPort;

public:

    static UdpManager& getUdp();

    //给 服务器ip和端口号 赋值的函数
    void setServerInfo(QString ip,quint16 port );


    void sendUdpJsonData();

};

#endif // UDPMANAGER_H
