#include "MainWindow.h"

#include <QApplication>

#include "UdpManager.h"

int main(int argc, char *argv[])
{
    //窗口控件显示不全，让程序适配高分辨率
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);

    //udp单例模式类中，公有下 设置ip和端口号
    UdpManager::getUdp().setServerInfo("127.0.0.1",12345);


    MainWindow w;
    w.show();

    return a.exec();
}
