#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("车载中控系统");
    this->setFixedSize(1024, 600);

    connect(ui->widget, &BottomBar::switchToHome,this,&MainWindow::dealToHome  );
    connect(ui->widget, &BottomBar::switchToAir,this,&MainWindow::dealToAir  );
    connect(ui->widget, &BottomBar::switchToTheme,this,&MainWindow::dealToTheme  );

    //配置 首页汽车按钮，切换主题页面信号与槽
    connect(ui->home,&HomeScreen::toHome,this,&MainWindow::dealToTheme  );

    //配置 更改主题的自定义信号与槽函数
    connect(ui->theme,&ThemeScreen::sendThemePath, this,&MainWindow::recvThemePath  );

    //配置 更改油耗的自定义信号与槽函数
    connect(ui->home,&HomeScreen::toFuleScreen, this,
            [this]()
    {
        //切换到 油耗页面
        ui->stackedWidget->setCurrentIndex(3);
    });

}

void MainWindow::recvThemePath(QString path)
{
    //1.切换页面管理器：显示 主页面
    ui->stackedWidget->setCurrentIndex(0);

    //2.更改HomeScreen背景图片
    ui->home->setBackgroundImg(path);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealToHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::dealToAir()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::dealToTheme()
{
    ui->stackedWidget->setCurrentIndex(1);
}



