#include "MyLabel.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent)  //初始化父类
{
    //样式表
    setStyleSheet(R"(
                QLabel{
                    color: white;
                    font-size: 16px;
                    background-color: rgba(51,51,51,0.7);
                    border-radius: 8px;
                    padding: 10px 20px;
                }
            )");
    //默认隐藏的状态
    hide();
    // show(); 显示label

    //创建定时器对象
    timer = new QTimer(this);

    //单步触发，不是循环执行
    timer->setSingleShot(true);

   //关联信号与槽 timeout  槽函数：隐藏label
    //定时器时间到，标签label隐藏
    connect(timer,&QTimer::timeout, this,  &QLabel::hide);
}

void MyLabel::toastLabel(QString str)
{
    //1)label控件显示内容
    setText(str);
    //2)label的大小 自适应文字内容
    this->adjustSize();

    //3)显示在所有控件的最上层
    raise();
    //4)显示label  show();
    show();

    //显示的位置？
    move(440 , 320);

   //5)开启定时器，间隔时间1秒
    timer->start(1000);

}
