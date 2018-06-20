#ifndef MYWIDGETS_H
#define MYWIDGETS_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QGuiApplication>
#include <QScreen>

/**
 * @brief The RenderArea class
 */
class SoundLevel : public QWidget
{
    Q_OBJECT

public:
    SoundLevel(QWidget *parent = 0);
    void setLevel(qreal value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    qreal m_level;
    QPixmap m_pixmap;
};

/**
 * @brief The ScreenRegion class
 */
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

class ColorPallete : public QWidget
{
    Q_OBJECT
public:
    explicit ColorPallete(QWidget *parent);
    void setColor(const QColor &color);
};

#endif // MYWIDGETS_H
