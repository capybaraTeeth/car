#include "ThemeScreen.h"
#include "ui_ThemeScreen.h"
#include <QDebug>
ThemeScreen::ThemeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景

    //主题图片：动漫风格壁纸
    imgPaths.push_back(":/background/konata/qcf1.jpg");
    imgPaths.push_back(":/background/konata/qcf3.jpg");
    imgPaths.push_back(":/background/konata/qcf4.jpg");
    imgPaths.push_back(":/background/konata/qcf5.jpg");
    imgPaths.push_back(":/background/konata/qcf6.jpg");
    imgPaths.push_back(":/background/konata/dkl.jpg");

    //循环向网格布局添加label
    for(int i=0;i<imgPaths.size(); i++)
    {
        //1.创建label
        QLabel* label  = new QLabel(this);
        //2.按照路径显示图片
        label->setPixmap(QPixmap(imgPaths.at(i)));
        //3.自适应大小
        label->setScaledContents(true);
        //（可选项）label的大小
        label->setFixedSize(220,150);
        //4.添加到布局中
        ui->gridLayout->addWidget(label, i/3 ,i%3);

        //5.安装监听器
        label->installEventFilter(this);
        //6.将label保存到容器中
        list_labels.push_back(label);
        //7.给标签对象设置一个 编号
        label->setObjectName(QString::number(i));
    }
}

bool ThemeScreen::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        //父子类指针的转换
        QLabel* label = dynamic_cast<QLabel*>( watched );
        if(label == nullptr)
        {
            return false;
        }

        //1.清除其他label的样式
        for( auto item : list_labels  )
        {
            item->setStyleSheet("border:2px solid transparent; border-radius:6px;");
        }
        //2.选择的label 背景高亮
        label->setStyleSheet("border:5px solid #1E90FF; border-radius:6px;");

        //3.将点击的label的编号记录
        currentIndex = label->objectName().toInt();

        return true;

    }

    return  QWidget::eventFilter(watched,event);
}


//更改主题
void ThemeScreen::on_pushButton_clicked()
{
    //获取选中的图片的路径
   QString path = imgPaths.at(currentIndex);
   //通过自定义信号 发出
   emit sendThemePath(path);

}

ThemeScreen::~ThemeScreen()
{
    delete ui;
}



