#include "ambilight.h"
#include "ui_ambilight.h"

Ambilight::Ambilight(QWidget *parent) :
    TabContent(parent),
    ambilightStarted(false),
    ui(new Ui::Ambilight)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
}

Ambilight::~Ambilight() {delete ui;}

QColor Ambilight::getAveragePixelColor(const QImage &img, int step)
{
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < img.width(); i += step)
        for (int j = 0 ; j < img.height(); j += step) {
            r += img.pixelColor(i, j).red();
            g += img.pixelColor(i, j).green();
            b += img.pixelColor(i, j).blue();
        }
    r /= img.width() * img.height() / (step * step);
    g /= img.width() * img.height() / (step * step);
    b /= img.width() * img.height() / (step * step);

    QColor color;
    color.setRed((r > 255 ? r = 255 : r));
    color.setGreen((g > 255 ? g = 255 : g));
    color.setBlue((b > 255 ? b = 255 : b));

    return color;
}

void Ambilight::timerUpdate()
{
    QRect selectedRegion = ui->screenRegion->getSelectedRegion();
    if (selectedRegion.isEmpty())
        return;

    QImage screenshot = QGuiApplication::primaryScreen()->grabWindow(0,
                        selectedRegion.x(), selectedRegion.y(),
                        selectedRegion.width(), selectedRegion.height()).toImage();

    //  Trying to optimize speed in the loop
    if (screenshot.width() >= 800 && screenshot.height() >= 500)
        color = getAveragePixelColor(screenshot, 20);
    else if (screenshot.width() <= 400 && screenshot.height() <= 400)
        color = getAveragePixelColor(screenshot, 4);
    else
        color = getAveragePixelColor(screenshot, 6);

    fillWidgetPallete(ui->colorPallete);
    sendDataToArduino();

    // if you turn this on, you will get dynamically changing picture, but it costs CPU !!!
    // repaint();
}

void Ambilight::on_pushButton_clicked()
{
    if (!ambilightStarted) {
        ambilightStarted = true;
        ui->pushButton->setText("Finish");

        //  Start timer . Is this aproximatelly 60+ fps ?
        timer->start(15);
    } else {
        ambilightStarted = false;
        ui->pushButton->setText("Start");

        //  Stop timer
        timer->stop();
    }
}

void Ambilight::clickStartButton()
{
    ui->pushButton->click();
}

