#include "AirScreen.h"
#include "ui_AirScreen.h"

#include "CarConfig.h"
#include "UdpManager.h"

AirScreen::AirScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirScreen)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景

   updateUi();

    //配置 温度发生改变的自定义信号与槽，来刷新温度值
    connect(&CarConfig::getConfig(),&CarConfig::sendNewTemperatuer,
            [this](int temp)
    {
       updateUi();
    });

    //配置文件中获取 风量的级别，初始化界面ui
    int level = CarConfig::getConfig().getLevel();
    ui->widget->setLevel(level);

    //初始化风向
    bool state_window = CarConfig::getConfig().isWindowOn();
    bool state_body = CarConfig::getConfig().isBodyOn();
    bool state_foot =CarConfig::getConfig().isFootOn();

    if(state_window)
        ui->label_window->setPixmap(QPixmap(":/background/air/up_open.png"));
    if(state_body)
        ui->label_boby2->setPixmap(QPixmap(":/background/air/mid_open.png"));
    if(state_foot)
        ui->label_foot->setPixmap(QPixmap(":/background/air/down_open.png"));


    //初始化按钮
    bool st_auto =  CarConfig::getConfig().isAutoOn();
    bool st_air =  CarConfig::getConfig().isAcOn();
    bool st_cold =  CarConfig::getConfig().isAcColdOn();
    bool st_REC =  CarConfig::getConfig().isRECOn();
    bool st_vent =  CarConfig::getConfig().isVentOn();
    bool st_def =  CarConfig::getConfig().isDEFOn();

    if(st_auto)
        ui->pushButton_auto->setIcon(QIcon(":/background/air/auto_icon_select.png"));
    if(st_air)
         ui->pushButton_wind->setIcon(QIcon(":/background/air/wind_btn_open.png"));
    if(st_cold)
         ui->pushButton_snow->setIcon(QIcon(":/background/air/snow_icon_select.png"));
    if(st_REC)
         ui->pushButton_loop->setIcon(QIcon(":/background/air/loop_open.png"));
    if(st_vent)
        ui->pushButton_tong->setIcon(QIcon(":/background/air/windding_select.png"));
    if(st_def)
        ui->pushButton_shuang->setIcon(QIcon(":/background/air/wram_seelct.png"));


    label = new MyLabel(this);
}

AirScreen::~AirScreen()
{
    delete ui;
}
//变大
void AirScreen::on_pushButton_up_clicked()
{
    //1)获取ini中温度
    int temp = CarConfig::getConfig().getTemperatuer();
    //2) 修改温度，重新保存到配置文件中
    CarConfig::getConfig().setTemperatuer(temp+1);
}
//变小
void AirScreen::on_pushButton_down_clicked()
{
    //1)获取ini中温度
    int temp = CarConfig::getConfig().getTemperatuer();
    //2) 修改温度，重新保存到配置文件中
    CarConfig::getConfig().setTemperatuer(temp-1);
}

void AirScreen::on_pushButton_auto_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isAutoOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setAutoOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {//:/background/air/auto_icon.png
        ui->pushButton_auto->setIcon(QIcon(":/background/air/auto_icon_select.png"));
    }else
    {
        ui->pushButton_auto->setIcon(QIcon(":/background/air/auto_icon.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "空调自动已开" : "空调自动已关");

}

void AirScreen::on_pushButton_wind_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isAcOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setAcOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_wind->setIcon(QIcon(":/background/air/wind_btn_open.png"));
    }else
    {
        ui->pushButton_wind->setIcon(QIcon(":/background/air/wind_btn_lock.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "空调已开" : "空调已关");
}

void AirScreen::on_pushButton_snow_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isAcColdOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setAcColdOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_snow->setIcon(QIcon(":/background/air/snow_icon_select.png"));
    }else
    {
        ui->pushButton_snow->setIcon(QIcon(":/background/air/snow_icon.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "制冷已开" : "制冷已关");
}

void AirScreen::on_pushButton_loop_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isRECOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setRECOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_loop->setIcon(QIcon(":/background/air/loop_open.png"));
    }else
    {
        ui->pushButton_loop->setIcon(QIcon(":/background/air/loop_lock.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "设置为内循环" : "设置为外循环");
}

void AirScreen::on_pushButton_tong_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isVentOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setVentOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_tong->setIcon(QIcon(":/background/air/windding_select.png"));
    }else
    {
        ui->pushButton_tong->setIcon(QIcon(":/background/air/windding.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "设置为通风模式" : "通风已关闭");
}

void AirScreen::on_pushButton_shuang_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().isDEFOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setDEFOn(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_shuang->setIcon(QIcon(":/background/air/wram_seelct.png"));
    }else
    {
        ui->pushButton_shuang->setIcon(QIcon(":/background/air/wram.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "前除霜已开启" : "前除霜已开启已关闭");
}

void AirScreen::on_pushButton_window_clicked()
{

    bool status = CarConfig::getConfig().isWindowOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setWindowOn(status);

    //根据新状态，更改按钮的图标
    if (status) {
        ui->label_window->setPixmap(QPixmap(":/background/air/up_open.png"));

    } else {
        ui->label_window->setPixmap(QPixmap(":/background/air/up_no.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

}

void AirScreen::on_pushButton_boby_clicked()
{
    bool status = CarConfig::getConfig().isBodyOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setBodyOn(status);

    //根据新状态，更改按钮的图标
    if (status) {
        ui->label_boby2->setPixmap(QPixmap(":/background/air/mid_open.png"));

    } else {
        ui->label_boby2->setPixmap(QPixmap(":/background/air/mid_no.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_foot_clicked()
{
    bool status = CarConfig::getConfig().isFootOn();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setFootOn(status);

    //根据新状态，更改按钮的图标
    if (status) {
        ui->label_foot->setPixmap(QPixmap(":/background/air/down_open.png"));

    } else {
        ui->label_foot->setPixmap(QPixmap(":/background/air/down_no.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();
}

void AirScreen::updateUi()
{
    //获取配置文件温度值，界面label显示
    int temp = CarConfig::getConfig().getTemperatuer();


    //设置三个label
    ui->currentTemp->setText(QString("%1℃").arg(temp));

    if(temp==16)
    {
        ui->loText->setText("Lo");
        ui->smallTemp->setNum(temp+1);
    } else if(temp==30)
    {
        ui->smallTemp->setText("Hi");
        ui->loText->setNum(temp-1);
    }else
    {
        ui->loText->setNum(temp-1);
        ui->smallTemp->setNum(temp+1);
    }
}








