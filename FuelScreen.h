#ifndef FUELSCREEN_H
#define FUELSCREEN_H

#include <QWidget>
//图表
#include <QChart>
//折线
#include <QLineSeries>
//数值类的y轴
#include <QValueAxis>
//日期类的x轴
#include <QDateTimeAxis>
#include <QAreaSeries>

//图表模块的命名空间
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class FuelScreen;
}

class FuelScreen : public QWidget
{
    Q_OBJECT

public:
    explicit FuelScreen(QWidget *parent = nullptr);
    ~FuelScreen();

private:
    Ui::FuelScreen *ui;
    //图表对象
    QChart * chart;
    //我的 线
    QLineSeries* m_line;
    QLineSeries* m_avg;

    //y轴（数值轴）
    QValueAxis* axisY;
    //x轴（日期轴）
    QDateTimeAxis* axisX;

    //面积轴，绿色的渐变效果范围
    QAreaSeries* area;
};

#endif // FUELSCREEN_H
