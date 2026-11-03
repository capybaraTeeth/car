#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
//自定义定时器
#include <QTimer>

//播放器对象
#include <QMediaPlayer>
#include <QList>
#include <QMediaMetaData>
#include "MyLabel.h"

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

    //更改背景的函数
    void setBackgroundImg(QString path);

signals:
    void toHome();
    void toFuleScreen();
private slots:
    void on_pushButton_car_clicked();

    void changeTimeLabel();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //处理媒体资源加载完成后
    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);

    void on_pushButton_lock_clicked();

    void on_pushButton_box_clicked();


private:
    void getMusicInfo();

private:
    Ui::HomeScreen *ui;
    QTimer* time;
    QMediaPlayer* player;
    QList<QString> musicPaths;
    int musicIndex = 0;
    //自定义label控件
    MyLabel* label;
};

#endif // HOMESCREEN_H
