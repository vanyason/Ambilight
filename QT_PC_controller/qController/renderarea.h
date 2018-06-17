#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    void setLevel(qreal value);

protected:
    void paintEvent(QPaintEvent *event);

private:
    qreal m_level;
    QPixmap m_pixmap;
};

#endif // RENDERAREA_H

