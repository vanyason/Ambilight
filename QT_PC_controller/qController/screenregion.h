#ifndef SCREENREGION_H
#define SCREENREGION_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>

class ScreenRegion : public QWidget
{
    Q_OBJECT

public:
    explicit ScreenRegion(QWidget *parent = 0);
    const QRect getSelectedRegion();

private:
    QRect selectionRect;
    bool selectionStarted;
    int xRatio, yRatio;

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // SCREENREGION_H
