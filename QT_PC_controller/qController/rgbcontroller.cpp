#include "rgbcontroller.h"
#include "ui_rgbcontroller.h"

RGBController::RGBController(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::RGBController)
{
    ui->setupUi(this);
    connect(ui->redSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
    connect(ui->greenSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
    connect(ui->blueSlider, SIGNAL(valueChanged(int)), SLOT(changeColor()));
}

RGBController::~RGBController() { delete ui; }

void RGBController::changeColor()
{
    color.setRgb(ui->redSlider->value(), ui->greenSlider->value(), ui->blueSlider->value());
    fillWidgetPallete(ui->colorPallete);
    sendDataToArduino();
}
