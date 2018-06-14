#include "screenregion.h"

ScreenRegion::ScreenRegion(QWidget *parent) : QWidget(parent),
    selectionRect(), selectionStarted(false)
{
    this->setGeometry(100, 10, 421, 241);   //  how to improve this code? this part sets up the real geometry of the widget

    //  get Ratio
    xRatio = QGuiApplication::primaryScreen()->grabWindow(0).width() / width();
    yRatio = QGuiApplication::primaryScreen()->grabWindow(0).height() / height();
}
const QRect ScreenRegion::getSelectedRegion()
{
    return QRect(xRatio * selectionRect.x(),
                 yRatio * selectionRect.y(),
                 xRatio * selectionRect.width(),
                 yRatio * selectionRect.height()).normalized();
}

void ScreenRegion::paintEvent(QPaintEvent *event)
{
    //  Set screenShot to pixmap
    QPixmap pixmap = QGuiApplication::primaryScreen()->grabWindow(0);
    pixmap = pixmap.scaled(this->width(), this->height(), Qt::IgnoreAspectRatio);

    //  draw pixmap to widget
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    //  Drawig selection region
    painter.begin(this);
    painter.setPen(QPen(QBrush(QColor(0, 0, 0, 180)), 1, Qt::DashLine));
    painter.setBrush(QBrush(QColor(255, 255, 255, 120)));
    painter.drawRect(selectionRect);
    painter.end();
}

void ScreenRegion::mouseMoveEvent(QMouseEvent *event)
{
    if (selectionStarted) {
        selectionRect.setBottomRight(event->pos());
        repaint();
    }
}

void ScreenRegion::mousePressEvent(QMouseEvent *event)
{
    selectionStarted = true;
    selectionRect.setTopLeft(event->pos());
    selectionRect.setBottomRight(event->pos());
}
void ScreenRegion::mouseReleaseEvent(QMouseEvent *event)
{
    selectionStarted = false;
}
