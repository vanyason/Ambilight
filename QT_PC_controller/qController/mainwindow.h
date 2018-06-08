#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QException>
#include <QSerialPort>
#include <QTextStream>

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

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSerialPort serialPort;
    QTextStream serialOut;
};

#endif // MAINWINDOW_H
