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

    //  Show color in the colorWidget
    QPalette pal(palette());
    pal.setColor(QPalette::Background, color);
    ui->colorPallete->setPalette(pal);

    //  Send data to Arduino com port
    *serialOut << "!" << " " <<  QVariant(color.red()).toString() << " " << QVariant(color.green()).toString() << " " << QVariant(color.blue()).toString() << endl;
}
