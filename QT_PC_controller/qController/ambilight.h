#ifndef AMBILIGHT_H
#define AMBILIGHT_H

#include <QDesktopWidget>
#include <QScreen>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include "tabcontent.h"

namespace Ui {
class Ambilight;
}

class Ambilight : public TabContent
{
    Q_OBJECT

public:
    explicit Ambilight(QWidget *parent = 0);
    ~Ambilight();
    bool ambilightStarted;
    void clickButton();

private slots:
    void on_pushButton_clicked();
    void timerUpdate();

private:
    Ui::Ambilight *ui;
    QTimer *timer;

    QImage screenshot, newScreenshot;
    int r0, g0, b0;
    int r1, g1, b1;
    QColor color1;
};

#endif // AMBILIGHT_H
