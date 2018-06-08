#include "tabcontent.h"

TabContent::TabContent(QWidget *parent) : QWidget(parent)
{}
TabContent::~TabContent() {}

void TabContent::linkPortData(QSerialPort &serialPort, QTextStream &serialOut)
{
    this->serialPort = &serialPort;
    this->serialOut = &serialOut;
}
