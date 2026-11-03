#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void dealToHome();
    void dealToAir();
    void dealToTheme();

    //响应更改主题槽函数
    void recvThemePath(QString path);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
