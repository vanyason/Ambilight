#ifndef AMBILIGHT_H
#define AMBILIGHT_H

#include "tabcontent.h"

namespace Ui {
class Ambilight;
}

class Ambilight : public TabContent
{
    Q_OBJECT

public:
    explicit Ambilight(QWidget *parent = 0);
    ~Ambilight();

private:
    Ui::Ambilight *ui;
};

#endif // AMBILIGHT_H
