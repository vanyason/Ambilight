#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  Link serial port
    ui->ambilight->linkPort(serialPort);
    ui->rgbCtrl->linkPort(serialPort);
    ui->lightMusic->linkPort(serialPort);

    //  Get info about available COM ports and set data to comboBox
    QList<QSerialPortInfo> portsList = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : portsList)
        ui->comboBox->addItem(info.portName());

    //  Setup tray icon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
    trayIcon->setToolTip("LED Controller");

    QAction *viewWindow = new QAction(trUtf8("Show"), this);
    QAction *quitAction = new QAction(trUtf8("Close"), this);

    QMenu *menu = new QMenu(this);
    menu->addAction(viewWindow);
    menu->addAction(quitAction);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    trayIcon->setContextMenu(menu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
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
        serialPort.setBaudRate(115200);
        serialPort.open(QIODevice::WriteOnly);
        cout << "Port: " << arg1 << " is setted" << endl;
    } catch (...) {
        cout << "Something wrong with COM port" << endl;
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (ui->ambilight->ambilightStarted)
        ui->ambilight->clickStartButton();
    if(ui->lightMusic->lightMusicStarted)
        ui->lightMusic->clickStartButton();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (this->isVisible()) {
        event->ignore();
        this->hide();
//        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
//        trayIcon->showMessage("Tray Program",
//                              trUtf8("Приложение свернуто в трей. Для того чтобы, "
//                                     "развернуть окно приложения, щелкните по иконке приложения в трее"),
//                              icon,
//                              2000);
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if (!this->isVisible()) {
            this->show();
        } else {
            this->hide();
        }

        break;
    default:
        break;
    }
}
