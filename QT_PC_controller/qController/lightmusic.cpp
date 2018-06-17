#include "lightmusic.h"
#include "ui_lightmusic.h"

const int BufferSize = 4096;

AudioInfo::AudioInfo(const QAudioFormat &format, QObject *parent)
    :   QIODevice(parent)
    ,   m_format(format)
    ,   m_maxAmplitude(0)
    ,   m_level(0.0)

{
    switch (m_format.sampleSize()) {
    case 8:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 255;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 127;
            break;
        default:
            break;
        }
        break;
    case 16:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 65535;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 32767;
            break;
        default:
            break;
        }
        break;

    case 32:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 0xffffffff;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 0x7fffffff;
            break;
        case QAudioFormat::Float:
            m_maxAmplitude = 0x7fffffff; // Kind of
        default:
            break;
        }
        break;

    default:
        break;
    }
}

AudioInfo::~AudioInfo() {}

void AudioInfo::start() {	open(QIODevice::WriteOnly);}

void AudioInfo::stop() {	close();}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)
    return 0;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    if (m_maxAmplitude) {
        Q_ASSERT(m_format.sampleSize() % 8 == 0);
        const int channelBytes = m_format.sampleSize() / 8;
        const int sampleBytes = m_format.channelCount() * channelBytes;
        Q_ASSERT(len % sampleBytes == 0);
        const int numSamples = len / sampleBytes;

        quint32 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < m_format.channelCount(); ++j) {
                quint32 value = 0;

                if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    value = *reinterpret_cast<const quint8 *>(ptr);
                } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    value = qAbs(*reinterpret_cast<const qint8 *>(ptr));
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint16>(ptr);
                    else
                        value = qFromBigEndian<quint16>(ptr);
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint16>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint16>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint32>(ptr);
                    else
                        value = qFromBigEndian<quint32>(ptr);
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint32>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint32>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::Float) {
                    value = qAbs(*reinterpret_cast<const float *>(ptr) * 0x7fffffff); // assumes 0-1.0
                }

                maxValue = qMax(value, maxValue);
                ptr += channelBytes;
            }
        }

        maxValue = qMin(maxValue, m_maxAmplitude);
        m_level = qreal(maxValue) / m_maxAmplitude;
    }

    emit update();
    return len;
}






LightMusic::LightMusic(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::LightMusic),
    audioInfo(0),
    audioInput(0),
    input(0),
    buffer(BufferSize, 0),
    audioDeviceInfo(QAudioDeviceInfo::defaultInputDevice())
{
    ui->setupUi(this);
    initializeWindow();
    initializeAudio();
}

LightMusic::~LightMusic()
{
    delete ui;
}

void LightMusic::initializeWindow()
{

    /*
     * Помещаем в комбобокс все аудио девайсы
     */
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
    ui->renderArea->setLevel(audioInfo->level());

    /*Sending data to arduino!*/
    color.setRed((int)255*audioInfo->level());
    qDebug() << audioInfo->level();
    fillWidgetPallete(ui->colorPallete);
    sendDataToArduino();
    update();




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
