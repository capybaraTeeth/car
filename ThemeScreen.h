#ifndef THEMESCREEN_H
#define THEMESCREEN_H

#include <QWidget>

//label头文件
#include <QLabel>
#include <QList>
#include <QDebug>

namespace Ui {
class ThemeScreen;
}

class ThemeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeScreen(QWidget *parent = nullptr);
    ~ThemeScreen();

    //重写虚函数：事件过滤
    bool eventFilter(QObject* watched, QEvent* event);

signals:
    void sendThemePath(QString path);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ThemeScreen *ui;
    //容器：存储图片路径的容器
     QList<QString> imgPaths;
    //容器：存储创建标签控件
     QList<QLabel*> list_labels;

     int currentIndex = 0;


};

#endif // THEMESCREEN_H
