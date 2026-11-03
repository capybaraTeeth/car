#ifndef CARCONFIG_H
#define CARCONFIG_H


#include <QSettings>
#include <QObject>
#include <QJsonObject>


class CarConfig  : public QObject
{
    //2)添加元对象的宏
    Q_OBJECT
     CarConfig();
     CarConfig(const CarConfig& o);
     //配置文件 读取键值对的对象
     QSettings* setting;
     static CarConfig instacne;

signals:
     //发出新的温度值
    void sendNewTemperatuer(int temp);
public:
     static CarConfig& getConfig();

     //车门锁
     //设置锁
     void setDoorLock( bool lock );
     //获取锁
     bool getDoorLock()const;

     //后备箱
     void setBoxLock( bool lock );
     //获取锁
     bool getBoxLock()const;

     //获取温度值
     int getTemperatuer()const;

     //设置温度值
     void setTemperatuer(int temp);

     //设置空调风量
    void setLevel(int l);
     //获取空调风量
     int getLevel() const;

     //空调一排按钮

     //自动
     bool isAutoOn() const;
     void setAutoOn(bool on);

     // 空调开关
     bool isAcOn() const;
     void setAcOn(bool on);

     //制冷
     bool isAcColdOn() const;
     void setAcColdOn(bool on);

     //内循环
     bool isRECOn() const;
     void setRECOn(bool on);

     //通风 Vent
     bool isVentOn() const;
     void setVentOn(bool on);

     //除霜Defrost
     bool isDEFOn() const;
     void setDEFOn(bool on);

     //空调吹风方向
     //玻璃
     bool isWindowOn() const;
     void setWindowOn(bool on);

     //身体
     bool isBodyOn() const;
     void setBodyOn(bool on);

     //脚
     bool isFootOn() const;
     void setFootOn(bool on);


     QJsonObject buildJsonObject();


};

#endif // CARCONFIG_H
