/********************************************************************************
** Form generated from reading UI file 'rgbcontroller.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGBCONTROLLER_H
#define UI_RGBCONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mywidgets.h>

QT_BEGIN_NAMESPACE

class Ui_RGBController
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    ColorPallete *colorPallete;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *redSlider;
    QSpinBox *redSpinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *greenSlider;
    QSpinBox *greenSpinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *blueSlider;
    QSpinBox *blueSpinBox;

    void setupUi(QWidget *RGBController)
    {
        if (RGBController->objectName().isEmpty())
            RGBController->setObjectName(QStringLiteral("RGBController"));
        RGBController->resize(527, 258);
        layoutWidget = new QWidget(RGBController);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 511, 221));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        colorPallete = new ColorPallete(layoutWidget);
        colorPallete->setObjectName(QStringLiteral("colorPallete"));
        colorPallete->setAutoFillBackground(true);

        verticalLayout->addWidget(colorPallete);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        redSlider = new QSlider(layoutWidget);
        redSlider->setObjectName(QStringLiteral("redSlider"));
        redSlider->setMaximum(255);
        redSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(redSlider);

        redSpinBox = new QSpinBox(layoutWidget);
        redSpinBox->setObjectName(QStringLiteral("redSpinBox"));
        redSpinBox->setMaximum(255);

        horizontalLayout->addWidget(redSpinBox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        greenSlider = new QSlider(layoutWidget);
        greenSlider->setObjectName(QStringLiteral("greenSlider"));
        greenSlider->setMaximum(255);
        greenSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(greenSlider);

        greenSpinBox = new QSpinBox(layoutWidget);
        greenSpinBox->setObjectName(QStringLiteral("greenSpinBox"));
        greenSpinBox->setMaximum(255);

        horizontalLayout_2->addWidget(greenSpinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        blueSlider = new QSlider(layoutWidget);
        blueSlider->setObjectName(QStringLiteral("blueSlider"));
        blueSlider->setMaximum(255);
        blueSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(blueSlider);

        blueSpinBox = new QSpinBox(layoutWidget);
        blueSpinBox->setObjectName(QStringLiteral("blueSpinBox"));
        blueSpinBox->setMaximum(255);

        horizontalLayout_3->addWidget(blueSpinBox);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(RGBController);
        QObject::connect(redSlider, SIGNAL(valueChanged(int)), redSpinBox, SLOT(setValue(int)));
        QObject::connect(greenSlider, SIGNAL(valueChanged(int)), greenSpinBox, SLOT(setValue(int)));
        QObject::connect(blueSlider, SIGNAL(valueChanged(int)), blueSpinBox, SLOT(setValue(int)));
        QObject::connect(blueSpinBox, SIGNAL(valueChanged(int)), blueSlider, SLOT(setValue(int)));
        QObject::connect(greenSpinBox, SIGNAL(valueChanged(int)), greenSlider, SLOT(setValue(int)));
        QObject::connect(redSpinBox, SIGNAL(valueChanged(int)), redSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(RGBController);
    } // setupUi

    void retranslateUi(QWidget *RGBController)
    {
        RGBController->setWindowTitle(QApplication::translate("RGBController", "Form", 0));
        label->setText(QApplication::translate("RGBController", "R", 0));
        label_2->setText(QApplication::translate("RGBController", "G", 0));
        label_3->setText(QApplication::translate("RGBController", "B", 0));
    } // retranslateUi

};

namespace Ui {
    class RGBController: public Ui_RGBController {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGBCONTROLLER_H
