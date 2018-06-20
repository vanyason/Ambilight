#include "mywidgets.h"

SoundLevel::SoundLevel(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    m_level = 0;
    setMinimumHeight(30);
    setMinimumWidth(200);
}

void SoundLevel::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(QRect(painter.viewport().left() + 10,
                           painter.viewport().top() + 10,
                           painter.viewport().right() - 20,
                           painter.viewport().bottom() - 20));
    if (m_level == 0.0)
        return;

    int pos = ((painter.viewport().right() - 20) - (painter.viewport().left() + 11)) * m_level;
    painter.fillRect(painter.viewport().left() + 11,
                     painter.viewport().top() + 10,
                     pos,
                     painter.viewport().height() - 21,
                     Qt::red);
}

void SoundLevel::setLevel(qreal value)
{
    m_level = value;
    update();
}


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

//  ------  Color Pallete   ------------------
//
ColorPallete::ColorPallete(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
}

void ColorPallete::setColor(const QColor &color)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    this->setPalette(pal);
}
