#ifndef RGBCONTROLLER_H
#define RGBCONTROLLER_H

#include "tabcontent.h"

namespace Ui {
class RGBController;
}

class RGBController : public TabContent
{
    Q_OBJECT

public:
    explicit RGBController(QWidget *parent = 0);
    ~RGBController();

private slots:
    void changeColor();

private:
    Ui::RGBController *ui;
};

#endif // RGBCONTROLLER_H
