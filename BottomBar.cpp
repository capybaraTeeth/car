#include "BottomBar.h"
#include "ui_BottomBar.h"
#include "CarConfig.h"

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景

    //点击返回按键时，将自定义信号 转发出去
    connect(ui->pushButton_back,&QPushButton::clicked,this,&BottomBar::switchToHome);
    connect(ui->pushButton_home,&QPushButton::clicked,this,&BottomBar::switchToHome);

    connect(ui->pushButton_set,&QPushButton::clicked,this,&BottomBar::switchToTheme);
    connect(ui->pushButton_air,&QPushButton::clicked,this,&BottomBar::switchToAir);


    //获取配置文件温度值，界面label显示
    int temp = CarConfig::getConfig().getTemperatuer();
    QString str = QString("%1℃").arg(temp);
    ui->label_temp->setText(str);  //20℃


    //参数1：CarConfig类型对象
    //lambda信号与槽
    connect(&CarConfig::getConfig(),&CarConfig::sendNewTemperatuer,this,
            [this]( int temp  )
    {
        QString str = QString("%1℃").arg(temp);
        ui->label_temp->setText(str);  //20℃
    }
    );


}

//变小
void BottomBar::on_pushButton_little_clicked()
{
    //1)获取ini中温度
    int temp = CarConfig::getConfig().getTemperatuer();
    //2) 修改温度，重新保存到配置文件中
    CarConfig::getConfig().setTemperatuer(temp-1);
}

//变大
void BottomBar::on_pushButton_up_clicked()
{
    //1)获取ini中温度
    int temp = CarConfig::getConfig().getTemperatuer();
    //2) 修改温度，重新保存到配置文件中
    CarConfig::getConfig().setTemperatuer(temp+1);
}


BottomBar::~BottomBar()
{
    delete ui;
}
