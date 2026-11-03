#include "HomeScreen.h"
#include "ui_HomeScreen.h"
#include <QDateTime>
#include "CarConfig.h"
#include "UdpManager.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景

    //创建对象
    time = new QTimer(this);

    //关联信号与槽，间隔时间到，发出timeout的信号
    connect(time,&QTimer::timeout,this,&HomeScreen::changeTimeLabel);
    //开启定时器 参数：设定间隔时间，毫秒为单位，1000毫秒--》1秒
    time->start(1000);

    player = new QMediaPlayer(this);

    //加载多首媒体音乐
    musicPaths.push_back("C:/Users/33068/Desktop/code/music/LBI利比（时柏尘） - 小城夏天.mp3");
    musicPaths.push_back("C:/Users/33068/Desktop/code/music/周深 - 大鱼.mp3");
    musicPaths.push_back("C:/Users/33068/Desktop/code/music/薛之谦 - 我知道你都知道.mp3");

    //播放器默认播放第一首
    //url:资源媒体的链接路径
    player->setMedia( QUrl::fromLocalFile(musicPaths.at(0)) );

    //当切换媒体音乐后，播放器会加载媒体资源，媒体资源加载完成后，才能获取歌曲的歌名或者缩略图
    connect(player,&QMediaPlayer::mediaStatusChanged,this, &HomeScreen::on_mediaStatusChanged);

    //获取配置文件 门锁的状态，初始化按钮的图标  0:上锁 1：开锁
    if(!CarConfig::getConfig().getDoorLock())
    {
        ui->pushButton_lock->setIcon(QIcon(":/background/main/suo.png"));
    }

    if(!CarConfig::getConfig().getBoxLock())
    {
        ui->pushButton_box->setIcon(QIcon(":/background/main/box_lock.png"));
    }

    //创建自定义标签控件
    label = new MyLabel(this);

    //信号转发
    connect(ui->pushButton_fule,&QPushButton::clicked, this,&HomeScreen::toFuleScreen);

}

//车门锁
void HomeScreen::on_pushButton_lock_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().getDoorLock();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setDoorLock(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_lock->setIcon(QIcon(":/background/main/unlock.png"));
    }else
    {
        ui->pushButton_lock->setIcon(QIcon(":/background/main/suo.png"));
    }
    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();

    //临时显示1秒提示 自定义label
    label->toastLabel(status? "四门已解锁" : "四门已上锁");
}


//后备箱按钮
void HomeScreen::on_pushButton_box_clicked()
{
    //获取门锁的状态 1
    bool status = CarConfig::getConfig().getBoxLock();

    //状态取反，保存新状态
    status = !status;
    CarConfig::getConfig().setBoxLock(status);

    //根据新状态，更改按钮的图标
    if(status)
    {
        ui->pushButton_box->setIcon(QIcon(":/background/main/box_open.png"));
    }else
    {
        ui->pushButton_box->setIcon(QIcon(":/background/main/box_lock.png"));
    }

    //发送udp指令
    UdpManager::getUdp().sendUdpJsonData();
    //临时显示1秒提示 自定义label
    label->toastLabel(status? "后备箱已开" : "后备箱已关");
}




//播放按钮
void HomeScreen::on_pushButton_clicked()
{
    //通过播放器的状态
    if(player->state() == QMediaPlayer::PausedState ||player->state() == QMediaPlayer::StoppedState )
    {
        player->play();
        //更改图标
        ui->pushButton->setIcon(QIcon(":/background/main/pause.png"));
    }else if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        //更改图标
        ui->pushButton->setIcon(QIcon(":/background/main/play.png"));
    }

}
//上一曲
void HomeScreen::on_pushButton_2_clicked()
{
    musicIndex = musicIndex == 0 ? musicPaths.size()-1 : musicIndex-1;
    player->setMedia(QUrl::fromLocalFile(musicPaths[musicIndex]));
    player->play();

}

//下一曲
void HomeScreen::on_pushButton_3_clicked()
{
    musicIndex = musicIndex == musicPaths.size()-1 ? 0 : musicIndex+1;
    player->setMedia(QUrl::fromLocalFile(musicPaths[musicIndex]));
    player->play();
}

void HomeScreen::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    //歌曲加载完毕 或者 缓冲完毕
    if(status == QMediaPlayer::LoadedMedia || QMediaPlayer::BufferedMedia)
    {
        getMusicInfo();
    }
}

void HomeScreen::getMusicInfo()
{
    QVariant title = player->metaData(QMediaMetaData::Title);//标题
    ui->label_name->setText(title.toString());

    // 先试封面，再试缩略图
    QVariant v = player->metaData(QMediaMetaData::CoverArtImage);//封面
    if (!v.isValid())
    {
        v = player->metaData(QMediaMetaData::ThumbnailImage);//缩略图
    }
    if (v.canConvert<QImage>())
    {
        QImage img = v.value<QImage>();
        if (!img.isNull())
        {
            ui->label_img->setPixmap(QPixmap::fromImage(img).scaled(
                ui->label_img->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }

}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::setBackgroundImg(QString path)
{
    //生成改背景图片的样式表
    QString style = QString("#home{border-image: url(%1);}").arg(path);
    //设置显示样式表
    this->setStyleSheet(style);
}


//首页 汽车按钮--》切换到更改主题页面
void HomeScreen::on_pushButton_car_clicked()
{
    emit toHome();
}

void HomeScreen::changeTimeLabel()
{
    //1.获取当前的 时间（年月日，时分秒）
    QDateTime dateTime = QDateTime::currentDateTime();
    //2.设定获取的时间的格式 分行显示：时：分钟
    //                           月/日 星期几

    //整合要显示的时间格式
    QString t = dateTime.toString(/*时间的格式*/ "HH:mm:ss");//小时:分钟:秒
    //获取:  月/日 星期几
    QString week =  dateTime.toString("MM/dd ddd");
    ui->label->setText(t+'\n'+week);

}


