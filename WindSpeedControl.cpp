#include "WindSpeedControl.h"
#include "CarConfig.h"
#include "UdpManager.h"

WindSpeedControl::WindSpeedControl(QWidget *parent) : QWidget(parent)
{

    setFixedHeight(50);
}

void WindSpeedControl::setLevel(int lvl, bool sendUdp)
{
    // 档位边界限制：最小0档
    if (lvl < 0) lvl = 0;
    // 档位边界限制：不超过最大档位
    if (lvl > m_maxLevel) lvl = m_maxLevel;
    // 如果档位发生变化才执行更新，避免重复操作
    if (m_level != lvl) {
        m_level = lvl;

        //保存风量级别值
        CarConfig::getConfig().setLevel(m_level);
        if (sendUdp) {
            //发送UDP JSON指令
           UdpManager::getUdp().sendUdpJsonData();
        }
        // 触发重绘，刷新UI显示
        update();
    }
}

void WindSpeedControl::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    // 开启抗锯齿，圆角更平滑
    p.setRenderHint(QPainter::Antialiasing);
    // 填充控件背景色：深蓝底色
    p.fillRect(rect(), QColor(10, 36, 71));

    int w = width();                // 控件总宽度
    int barHeight = 14;             // 每一格档位条的高度
    int step = w / (m_maxLevel + 1);// 每个档位格子的宽度
    int y = height() / 2 - barHeight / 2; // 垂直居中Y坐标

    // 绘制背景档位
    for (int i = 0; i <= m_maxLevel; ++i) {
        int x = i * step;
        // 单个档位矩形，左右留4px边距
        QRect r(x + 4, y, step - 8, barHeight);
        p.setPen(Qt::NoPen);// 取消边框线

        if (i <= m_level)
            p.setBrush(QColor(30, 144, 255)); // 当前档位及之前：亮蓝色高亮
        else
            p.setBrush(QColor(80, 80, 80));// 未选中档位：灰色
        // 绘制圆角矩形档位块，圆角半径3
        p.drawRoundedRect(r, 3, 3);
    }
}

void WindSpeedControl::mousePressEvent(QMouseEvent *event)
{
    // 获取鼠标点击的X坐标
    int pos = event->x();
    int step = width() / (m_maxLevel + 1);
    // 根据点击位置计算选中的档位
    int lvl = pos / step;
    // 设置档位（默认不传第二个参数sendUdp，按函数默认参数发送udp）
    setLevel(lvl);
}
