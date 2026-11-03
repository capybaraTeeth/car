#include "CarConfig.h"

//调用构造函数，创建对象
CarConfig CarConfig::instacne;

CarConfig &CarConfig::getConfig()
{
    //    //局部静态，只会初始化一次（构造函数只会调用一次）
    //    static CarConfig instacne;
    return instacne;
}

CarConfig::CarConfig()
{
    //创建配置文件对象   参数1：配置文件名称,默认生成在构建目录下
    setting = new QSettings("config.ini",QSettings::IniFormat);

    //初始化 默认值
    if(!setting->contains("/car_status/door_lock"))//配置文件中 判断某一个键值对是否存在
    {
        setting->setValue("/car_status/door_lock",0);
    }
    if(!setting->contains("/car_status/box_lock"))//配置文件中 判断某一个键值对是否存在
    {
        setting->setValue("/car_status/box_lock",0);
    }
    if(!setting->contains("/car_air/temperatuer"))//配置文件中 判断某一个键值对是否存在
    {
        setting->setValue("/car_air/temperatuer",20);
    }
    if (!setting->contains("CAR_STATUS/ac_power")) {
        setting->setValue("CAR_STATUS/ac_power", 0);
    }
    if (!setting->contains("CAR_STATUS/level")) {
        setting->setValue("CAR_STATUS/level", 3);
    }
    if (!setting->contains("CAR_STATUS/air_window")) {
        setting->setValue("CAR_STATUS/air_window", 0);
    }
    if (!setting->contains("CAR_STATUS/air_body")) {
        setting->setValue("CAR_STATUS/air_body", 0);
    }
    if (!setting->contains("CAR_STATUS/air_foot")) {
        setting->setValue("CAR_STATUS/air_foot", 0);
    }

    if (!setting->contains("AIR_STATUS/air_cold")) {
        setting->setValue("AIR_STATUS/air_cold", 0);
    }
    if (!setting->contains("AIR_STATUS/air_REC")) {
        setting->setValue("AIR_STATUS/air_REC", 0);
    }
    if (!setting->contains("AIR_STATUS/air_Vent")) {
        setting->setValue("AIR_STATUS/air_Vent", 0);
    }
    if (!setting->contains("AIR_STATUS/air_DEF")) {
        setting->setValue("AIR_STATUS/air_DEF", 0);
    }
    if (!setting->contains("AIR_STATUS/air_auto")) {
        setting->setValue("AIR_STATUS/air_auto", 0);
    }

}

bool CarConfig::isAcOn() const
{
    return setting->value("CAR_STATUS/ac_power", 0).toBool();
}

void CarConfig::setAcOn(bool on)
{
    setting->setValue("CAR_STATUS/ac_power", on ? 1 : 0);
}

int CarConfig::getTemperatuer() const
{
    return setting->value("/car_air/temperatuer").toInt();
}

void CarConfig::setTemperatuer(int temp)
{
    if(temp < 16) temp = 16;
    if(temp > 30) temp = 30;

    //向配置文件中 插入键值对
    setting->setValue("/car_air/temperatuer",temp );

    //只要温度发生了改变，同时通知 导航栏和空调页面，刷新界面温度
    emit sendNewTemperatuer(temp);
}

QJsonObject CarConfig::buildJsonObject()
{
    /*
     {
        "car_doorlock":0,
        "car_boxlock":1,
        "temp":20
    }
      */
    QJsonObject obj;
    //插入键值对
    obj["car_doorlock"] = getDoorLock();
    obj["car_boxlock"] = getBoxLock();
    obj["temp"] = getTemperatuer();

    obj["level"] = getLevel();

    obj["ac_power"] = isAcOn();                 // 空调开关
    // 空调风向
    obj["air_window"] = isWindowOn();           // 吹玻璃
    obj["air_body"] = isBodyOn();               // 吹身体
    obj["air_foot"] = isFootOn();               // 吹脚

    // 空调功能按钮
    obj["air_auto"] = isAutoOn();               // 自动模式
    obj["air_cold"] = isAcColdOn();             // 制冷
    obj["air_REC"] = isRECOn();                 // 内循环
    obj["air_Vent"] = isVentOn();               // 通风
    obj["air_DEF"] = isDEFOn();                 // 除霜
    return obj;

}

CarConfig::CarConfig(const CarConfig &o)
{

}


void CarConfig::setDoorLock(bool lock)
{
    //配置文件：[car_status]door_lock:  1

    //向配置文件中 插入键值对
    setting->setValue("/car_status/door_lock", lock?1:0 );
}

bool CarConfig::getDoorLock() const
{
    return  setting->value("/car_status/door_lock").toBool();
}

void CarConfig::setBoxLock(bool lock)
{
    //向配置文件中 插入键值对
    setting->setValue("/car_status/box_lock", lock?1:0 );
}

bool CarConfig::getBoxLock() const
{
    return  setting->value("/car_status/box_lock").toBool();
}


void CarConfig::setLevel(int l)
{
    setting->setValue("/car_air/level", l );
}

int CarConfig::getLevel() const
{
    return  setting->value("/car_air/level").toInt();
}

bool CarConfig::isAutoOn() const
{
    return setting->value("AIR_STATUS/air_auto", 0).toBool();
}

void CarConfig::setAutoOn(bool on)
{
    setting->setValue("AIR_STATUS/air_auto", on ? 1 : 0);
}

bool CarConfig::isAcColdOn() const
{
    return setting->value("AIR_STATUS/air_cold", 0).toBool();
}

void CarConfig::setAcColdOn(bool on)
{
    setting->setValue("AIR_STATUS/air_cold", on ? 1 : 0);
}

bool CarConfig::isRECOn() const
{
    return setting->value("AIR_STATUS/air_REC", 0).toBool();
}

void CarConfig::setRECOn(bool on)
{
    setting->setValue("AIR_STATUS/air_REC", on ? 1 : 0);
}

bool CarConfig::isVentOn() const
{
    return setting->value("AIR_STATUS/air_Vent", 0).toBool();
}

void CarConfig::setVentOn(bool on)
{
    setting->setValue("AIR_STATUS/air_Vent", on ? 1 : 0);
}

bool CarConfig::isDEFOn() const
{
    return setting->value("AIR_STATUS/air_DEF", 0).toBool();
}

void CarConfig::setDEFOn(bool on)
{
    setting->setValue("AIR_STATUS/air_DEF", on ? 1 : 0);
}


bool CarConfig::isWindowOn() const
{
    return setting->value("CAR_STATUS/air_window", 0).toBool();
}

void CarConfig::setWindowOn(bool on)
{
    setting->setValue("CAR_STATUS/air_window", on ? 1 : 0);
}

bool CarConfig::isBodyOn() const
{
    return setting->value("CAR_STATUS/air_body", 0).toBool();
}

void CarConfig::setBodyOn(bool on)
{
    setting->setValue("CAR_STATUS/air_body", on ? 1 : 0);
}

bool CarConfig::isFootOn() const
{
    return setting->value("CAR_STATUS/air_foot", 0).toBool();
}

void CarConfig::setFootOn(bool on)
{
    setting->setValue("CAR_STATUS/air_foot", on ? 1 : 0);
}

