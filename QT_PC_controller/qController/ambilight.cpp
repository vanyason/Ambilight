#include "ambilight.h"
#include "ui_ambilight.h"

Ambilight::Ambilight(QWidget *parent) :
    TabContent(parent),
    ui(new Ui::Ambilight)
{
    ui->setupUi(this);
}

Ambilight::~Ambilight()
{
    delete ui;
}
