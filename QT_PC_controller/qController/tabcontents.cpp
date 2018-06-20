#include "tabcontents.h"
#include "mywidgets.h"
#include "ui_rgbcontroller.h"
#include "ui_ambilight.h"
#include "ui_lightmusic.h"

//  --------    Tab Content  -------------------
//
TabContent::TabContent(QWidget *parent) : QWidget(parent)
{}
TabContent::~TabContent() {}

void TabContent::linkPort(QSerialPort &serialPort)
{
    this->serialPort = &serialPort;
}

void TabContent::sendDataToArduino()
{
    char output[4] = {'!', (char)color.red(), (char)color.green(), (char)color.blue()};
    serialPort->flush();
    serialPort->write(output, 4);
}

//  ----------  RGB Controller  ------------------
//
RGBController::RGBController(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::RGBController)
{
    ui->setupUi(this);
    connect(ui->redSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
}

RGBController::~RGBController() { delete ui; }

void RGBController::changeColor()
{
    color.setRgb(ui->redSlider->value(), ui->greenSlider->value(), ui->blueSlider->value());
    ui->colorPallete->setColor(color);
    sendDataToArduino();
}

//  ---------   Ambilight   ----------------------------
//
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

    ui->colorPallete->setColor(color);
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

//  ---------   Light Music   ----------------------------
//
LightMusic::LightMusic(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::LightMusic),
    audioInfo(0),
    audioInput(0),
    input(0),
    buffer(BufferSize, 0),
    lightMusicStarted(false),
    audioDeviceInfo(QAudioDeviceInfo::defaultInputDevice()),
    mode(NULL)
{

    ui->setupUi(this);
    ui->modeBox->addItem("Rainbow mode");
    ui->modeBox->addItem("Color picks");
    initializeWindow();
    initializeAudio();
}

LightMusic::~LightMusic()
{
    delete ui;
    if (mode)
        delete mode;
}

void LightMusic::clickStartButton()
{
    ui->pushButton->click();
}

void LightMusic::initializeWindow()
{
    const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
    ui->deviceBox->addItem(defaultDeviceInfo.deviceName(), qVariantFromValue(defaultDeviceInfo));
    foreach (const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioInput)) {
        if (deviceInfo != defaultDeviceInfo)
            ui->deviceBox->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }
    connect(ui->deviceBox, SIGNAL(activated(int)), SLOT(deviceChanged(int)));
    connect(ui->volumelSlider, SIGNAL(valueChanged(int)), SLOT(sliderChanged(int)));
}

void LightMusic::initializeAudio()
{
    audioFormat.setSampleRate(8000);
    audioFormat.setChannelCount(1);
    audioFormat.setSampleSize(16);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setCodec("audio/pcm");

    QAudioDeviceInfo info(audioDeviceInfo);
    if (!info.isFormatSupported(audioFormat)) {
        qWarning() << "Default format not supported - trying to use nearest";
        audioFormat = info.nearestFormat(audioFormat);
    }

    if (audioInfo)
        delete audioInfo;
    audioInfo  = new AudioInfo(audioFormat, this);
    connect(audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));

    createAudioInput();
}

void LightMusic::createAudioInput()
{
    audioInput = new QAudioInput(audioDeviceInfo, audioFormat, this);
    ui->volumelSlider->setValue(audioInput->volume() * 100);
    audioInfo->start();
    audioInput->start(audioInfo);
}

void LightMusic::refreshDisplay()
{
    ui->soundLevel->setLevel(audioInfo->level());
}

void LightMusic::readMore()
{
    if (!audioInput)
        return;
    qint64 len = audioInput->bytesReady();
    if (len > BufferSize)
        len = BufferSize;
    qint64 l = input->read(buffer.data(), len);
    if (l > 0)
        audioInfo->write(buffer.constData(), l);
}

void LightMusic::deviceChanged(int index)
{
    audioInfo->stop();
    audioInput->stop();
    audioInput->disconnect(this);
    delete audioInput;

    audioDeviceInfo = ui->deviceBox->itemData(index).value<QAudioDeviceInfo>();
    initializeAudio();
}

void LightMusic::sliderChanged(int value)
{
    if (audioInput)
        audioInput->setVolume(qreal(value) / 100);
}

void LightMusic::on_pushButton_clicked()
{
    if (!lightMusicStarted) {
        ui->pushButton->setText("Finish");
        connect(audioInfo, SIGNAL(update()), SLOT(outputColor()));
        lightMusicStarted = true;
    } else {
        ui->pushButton->setText("Start");
        audioInfo->disconnect(this, SLOT(outputColor()));
        lightMusicStarted = false;
    }
}

/**
 * @brief LightMusic::outputColor all the color modes
 * are here
 */
void LightMusic::outputColor()
{
    color = mode->handleSoundLevel(audioInfo->level());
    ui->colorPallete->setColor(color);
    sendDataToArduino();
}

void LightMusic::on_modeBox_currentIndexChanged(int index)
{
    if (mode)
        delete mode;
    switch (index) {
    case 0:
        mode = new Mode1();
        break;
    case 1:
        mode = new Mode2();
        break;
    default:
        break;
    }
}
