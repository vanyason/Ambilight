#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QSerialPort>
#include <QTextStream>
#include <QDebug>
#include <QTimer>

#include "mywidgets.h"
#include "audioinfo.h"
#include "lightmusicmode.h"

namespace Ui {
class RGBController;
class Ambilight;
class LightMusic;
}

/**
 * @brief The TabContent class
 */
class TabContent : public QWidget
{
    Q_OBJECT

public:
    explicit TabContent(QWidget *parent = 0);
    virtual ~TabContent();
    void linkPort(QSerialPort &serialPort);

protected:
    QSerialPort *serialPort;
    QColor color;

    void sendDataToArduino();    
};

/**
 * @brief The RGBController class
 */
class RGBController : public TabContent
{
    Q_OBJECT

public:
    explicit RGBController(QWidget *parent = 0);
    ~RGBController();

private slots:
    void changeColor();

private:
    Ui::RGBController *ui;
};

/**
 * @brief The Ambilight class
 */
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

/**
 * @brief The LightMusic class
 */
class LightMusic : public TabContent
{
    Q_OBJECT

public:
    explicit LightMusic(QWidget *parent = 0);
    ~LightMusic();

    bool lightMusicStarted;
    void clickStartButton();

private:   
    void initializeWindow();
    void initializeAudio();
    void createAudioInput();

private slots:
    void refreshDisplay();
    void outputColor();
    void readMore();
    void deviceChanged(int index);
    void sliderChanged(int value);
    void on_pushButton_clicked();
    void on_modeBox_currentIndexChanged(int index);

private:
     Ui::LightMusic *ui;

    QAudioDeviceInfo audioDeviceInfo;
    AudioInfo *audioInfo;
    QAudioFormat audioFormat;
    QAudioInput *audioInput;
    QIODevice *input;
    bool m_pullMode;
    QByteArray buffer;    
    LightMusicMode *mode;
};
#endif // TABCONTENT_H
