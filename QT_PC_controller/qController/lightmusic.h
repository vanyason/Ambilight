#ifndef LIGHTMUSIC_H
#define LIGHTMUSIC_H

#include "tabcontent.h"
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <qendian.h>
#include <QByteArray>
#include <QDebug>

namespace Ui {
class LightMusic;
}

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();

    void start();
    void stop();

    qreal level() const { return m_level; }
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude;
    qreal m_level; // 0.0 <= m_level <= 1.0

signals:
    void update();
};


class LightMusic : public TabContent
{
    Q_OBJECT

public:
    explicit LightMusic(QWidget *parent = 0);
    ~LightMusic();

private:
    Ui::LightMusic *ui;
    void initializeWindow();
    void initializeAudio();
    void createAudioInput();

private slots:
    void refreshDisplay();
    void readMore();
    void deviceChanged(int index);
    void sliderChanged(int value);

private:
    QAudioDeviceInfo audioDeviceInfo;
    AudioInfo *audioInfo;
    QAudioFormat audioFormat;
    QAudioInput *audioInput;
    QIODevice *input;
    bool m_pullMode;
    QByteArray buffer;
};

#endif // LIGHTMUSIC_H
