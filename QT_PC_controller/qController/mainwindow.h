#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QException>
#include <QSerialPort>
#include <QTextStream>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>

#include "tabcontent.h"
#include "rgbcontroller.h"
#include "ambilight.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * event);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_tabWidget_currentChanged(int index);
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    QSerialPort serialPort;
    QTextStream serialOut;
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
