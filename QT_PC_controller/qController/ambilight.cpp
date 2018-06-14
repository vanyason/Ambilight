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

void Ambilight::timerUpdate()
{
    QRect selectedRegion = ui->screenRegion->getSelectedRegion();

    if (selectedRegion.isEmpty())
        return;

    QImage screenshot = QGuiApplication::primaryScreen()->grabWindow(0, selectedRegion.x(), selectedRegion.y(),
                        selectedRegion.width(), selectedRegion.height()).toImage();

    //  get average pixel
    int r = 0, g = 0, b = 0;
    for (int i = 0; i < screenshot.width(); i += 2)
        for (int j = 0 ; j < screenshot.height(); j += 2) {
            r += screenshot.pixelColor(i, j).red();
            g += screenshot.pixelColor(i, j).green();
            b += screenshot.pixelColor(i, j).blue();
        }
    r /= screenshot.width() * screenshot.height() / 4;
    g /= screenshot.width() * screenshot.height() / 4;
    b /= screenshot.width() * screenshot.height() / 4;

    //qDebug() << r << " " << g << " " << b;

    color.setRed((r > 255 ? r = 255 : r));
    color.setGreen((g > 255 ? g = 255 : g));
    color.setBlue((b > 255 ? b = 255 : b));

    //  Show color in the colorWidget
    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    ui->colorPallete->setPalette(pal);

    //  Send data to Arduino com port
    *serialOut << "!" << " " <<  QVariant(color.red()).toString() << " " << QVariant(color.green()).toString() << " " << QVariant(color.blue()).toString() << endl;

    // if you turn this on, you will get dynamically changing picture, but it costs CPU !!!
    // repaint();

}

void Ambilight::on_pushButton_clicked()
{
    if (!ambilightStarted) {
        ambilightStarted = true;
        ui->pushButton->setText("Finish");

        //  Start timer
        timer->start(100);

    } else {
        ambilightStarted = false;
        ui->pushButton->setText("Start");

        //  Stop timer
        timer->stop();
    }
}

void Ambilight::clickButton()
{
    ui->pushButton->click();
}

