#ifndef AIRSCREEN_H
#define AIRSCREEN_H

#include <QWidget>
#include "MyLabel.h"

namespace Ui {
class AirScreen;
}

class AirScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AirScreen(QWidget *parent = nullptr);
    ~AirScreen();

private slots:
    void on_pushButton_up_clicked();

    void on_pushButton_down_clicked();

    void on_pushButton_auto_clicked();

    void on_pushButton_wind_clicked();

    void on_pushButton_snow_clicked();

    void on_pushButton_loop_clicked();

    void on_pushButton_tong_clicked();

    void on_pushButton_shuang_clicked();

    void on_pushButton_window_clicked();

    void on_pushButton_boby_clicked();

    void on_pushButton_foot_clicked();
private:
    Ui::AirScreen *ui;
    void updateUi();
    MyLabel* label;
};

#endif // AIRSCREEN_H
