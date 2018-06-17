#include "tabcontent.h"

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
    serialPort->write(output,4);
}

void TabContent::fillWidgetPallete(QWidget *widget)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    widget->setPalette(pal);
}
