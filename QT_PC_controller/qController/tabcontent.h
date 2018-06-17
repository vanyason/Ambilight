#ifndef TABCONTENT_H
#define TABCONTENT_H

#include <QWidget>
#include <QSerialPort>
#include <QTextStream>

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
    void fillWidgetPallete(QWidget *widget);
};

#endif // TABCONTENT_H
