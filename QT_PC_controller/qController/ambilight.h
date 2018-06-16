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
    void clickStartButton();

private slots:
    void on_pushButton_clicked();
    void timerUpdate();

private:
    Ui::Ambilight *ui;
    QTimer *timer;
    QImage screenshot;

    /**
     * @brief getAveragePixelColor
     * @param img Source image to analyse
     * @param step How many pixels to skip during an iteration in the loop
     * @return Average pixel color
     */
    QColor getAveragePixelColor(const QImage &img, int step = 4);
};

#endif // AMBILIGHT_H
