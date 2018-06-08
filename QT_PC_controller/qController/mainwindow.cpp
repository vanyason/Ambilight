#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  Add tabs
    TabContent *rgb = new RGBController();
    TabContent *ambilight = new Ambilight();
    rgb->linkPortData(serialPort, serialOut);
    ambilight->linkPortData(serialPort, serialOut);
    ui->tabWidget->addTab(rgb, "RGB Controller");
    ui->tabWidget->addTab(ambilight, "Ambilight");

    //  Get info about available COM ports and set data to comboBox
    QList<QSerialPortInfo> portsList = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : portsList)
        ui->comboBox->addItem(info.portName());
}
MainWindow::~MainWindow() {	delete ui;}

/*
 * Tries to open COM port for a further work;
 */
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QTextStream cout(stdout);
    try {
        serialPort.close();
        serialPort.setPortName(arg1);
        serialPort.setBaudRate(9600);
        serialPort.open(QIODevice::WriteOnly);
        serialOut.setDevice(&serialPort);
        cout << "Port: " << arg1 << " is setted" << endl;
    } catch (...) {
        cout << "Something wrong with COM port" << endl;
    }
}
