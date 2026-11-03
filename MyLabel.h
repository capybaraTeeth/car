#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QTimer>



class MyLabel : public QLabel
{
    Q_OBJECT
public:
    MyLabel(QWidget* parent = nullptr );

    //自定义标签显示内容的函数（显示内容+显示1秒）
    void toastLabel(QString str);

private:
    //自定义定时器
    QTimer* timer;
};

#endif // MYLABEL_H
