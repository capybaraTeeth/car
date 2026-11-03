#ifndef BOTTOMBAR_H
#define BOTTOMBAR_H

#include <QWidget>

namespace Ui {
class BottomBar;
}

class BottomBar : public QWidget
{
    Q_OBJECT

public:
    explicit BottomBar(QWidget *parent = nullptr);
    ~BottomBar();


signals:
    void switchToHome();
    void switchToTheme();
    void switchToAir();
private slots:
    void on_pushButton_little_clicked();

    void on_pushButton_up_clicked();

private:
    Ui::BottomBar *ui;
};

#endif // BOTTOMBAR_H
