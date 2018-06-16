#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QTextStream>
#include <QSerialPort>

class TabContent : public QWidget
{
    Q_OBJECT
public:
    explicit TabContent(QWidget *parent = 0);
    virtual ~TabContent();
    void linkPortData(QSerialPort &serialPort, QTextStream &serialOut);
protected:
    QSerialPort *serialPort;
    QTextStream *serialOut;
    QColor color;

    void sendDataToArduino();
    void fillWidgetPallete(QWidget *widget);
};

#endif // TABCONTENT_H
