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

    screenshot = QGuiApplication::primaryScreen()->grabWindow(0, 0, 0,
                 10, 10).toImage();

    for (int i = 0; i < screenshot.width(); i += 2)
        for (int j = 0 ; j < screenshot.height(); j += 2) {
            r0 += screenshot.pixelColor(i, j).red();
            g0 += screenshot.pixelColor(i, j).green();
            b0 += screenshot.pixelColor(i, j).blue();
        }
    r0 /= screenshot.width() * screenshot.height() / 4;
    g0 /= screenshot.width() * screenshot.height() / 4;
    b0 /= screenshot.width() * screenshot.height() / 4;

    color.setRed((r0 > 255 ? r0 = 255 : r0));
    color.setGreen((g0 > 255 ? g0 = 255 : g0));
    color.setBlue((b0 > 255 ? b0 = 255 : b0));

}

Ambilight::~Ambilight() {delete ui;}


void Ambilight::timerUpdate()
{

    QRect selectedRegion = ui->screenRegion->getSelectedRegion();

    if (selectedRegion.isEmpty())
        return;

    newScreenshot = QGuiApplication::primaryScreen()->grabWindow(0, selectedRegion.x(), selectedRegion.y(),
                    selectedRegion.width(), selectedRegion.height()).toImage();

    //  get average pixel
    for (int i = 0; i < newScreenshot.width(); i += 2)
        for (int j = 0 ; j < newScreenshot.height(); j += 2) {
            r1 += newScreenshot.pixelColor(i, j).red();
            g1 += newScreenshot.pixelColor(i, j).green();
            b1 += newScreenshot.pixelColor(i, j).blue();
        }
    r1 /= newScreenshot.width() * newScreenshot.height() / 4;
    g1 /= newScreenshot.width() * newScreenshot.height() / 4;
    b1 /= newScreenshot.width() * newScreenshot.height() / 4;

    //qDebug() << r << " " << g << " " << b;


    color1.setRed((r1 > 255 ? r1 = 255 : r1));
    color1.setGreen((g1 > 255 ? g1 = 255 : g1));
    color1.setBlue((b1 > 255 ? b1 = 255 : b1));


    int rdiff;
    int gdiff;
    int bdiff;
    //  While color != color1
    while (color != color1) {
        //  Show color in the colorWidget
        QPalette pal(palette());
        pal.setColor(QPalette::Background, color);
        ui->colorPallete->setPalette(pal);

        //  Send data to Arduino com port
        *serialOut << "!" << " " <<  QVariant(color.red()).toString() << " " << QVariant(color.green()).toString() << " " << QVariant(color.blue()).toString() << endl;


        rdiff = color1.red() - color.red();
        gdiff = color1.green() - color.green();
        bdiff = color1.blue() - color.blue();


        if(rdiff!=0)
            (rdiff < 0 ? color.setRed(color.red()-1) : color.setRed(color.red()+1));
        if(gdiff!=0)
            (gdiff < 0 ? color.setGreen(color.green()-1) : color.setGreen(color.green()+1));
        if(bdiff!=0)
            (bdiff < 0 ? color.setBlue(color.blue()-1) : color.setBlue(color.blue()+1));

        qDebug() << color1.red() << " " << color.red() <<
         " " << color1.green() << " " << color.green() <<
          " " << color1.blue() << " " << color.blue();

    }

    screenshot = newScreenshot;
}

//	//  Show color in the colorWidget
//	QPalette pal(palette());
//	pal.setColor(QPalette::Background, color);
//	ui->colorPallete->setPalette(pal);

//	//  Send data to Arduino com port
//	*serialOut << "!" << " " <<  QVariant(color.red()).toString() << " " << QVariant(color.green()).toString() << " " << QVariant(color.blue()).toString() << endl;

    // if you turn this on, you will get dynamically changing picture, but it costs CPU !!!
    // repaint();



/*void Ambilight::timerUpdate()
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

}*/

void Ambilight::on_pushButton_clicked()
{
    if (!ambilightStarted) {
        ambilightStarted = true;
        ui->pushButton->setText("Finish");

        //  Start timer
        timer->start(30);

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

