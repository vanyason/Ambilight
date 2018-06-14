/********************************************************************************
** Form generated from reading UI file 'ambilight.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMBILIGHT_H
#define UI_AMBILIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <screenregion.h>

QT_BEGIN_NAMESPACE

class Ui_Ambilight
{
public:
    QPushButton *pushButton;
    ScreenRegion *screenRegion;
    QWidget *colorPallete;

    void setupUi(QWidget *Ambilight)
    {
        if (Ambilight->objectName().isEmpty())
            Ambilight->setObjectName(QStringLiteral("Ambilight"));
        Ambilight->resize(527, 258);
        Ambilight->setAutoFillBackground(true);
        pushButton = new QPushButton(Ambilight);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 20, 85, 29));
        screenRegion = new ScreenRegion(Ambilight);
        screenRegion->setObjectName(QStringLiteral("screenRegion"));
        screenRegion->setGeometry(QRect(100, 10, 421, 241));
        screenRegion->setCursor(QCursor(Qt::CrossCursor));
        screenRegion->setAutoFillBackground(false);
        colorPallete = new QWidget(Ambilight);
        colorPallete->setObjectName(QStringLiteral("colorPallete"));
        colorPallete->setGeometry(QRect(10, 70, 81, 181));
        colorPallete->setAutoFillBackground(true);

        retranslateUi(Ambilight);

        QMetaObject::connectSlotsByName(Ambilight);
    } // setupUi

    void retranslateUi(QWidget *Ambilight)
    {
        Ambilight->setWindowTitle(QApplication::translate("Ambilight", "Form", 0));
        pushButton->setText(QApplication::translate("Ambilight", "Start", 0));
#ifndef QT_NO_TOOLTIP
        screenRegion->setToolTip(QString());
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class Ambilight: public Ui_Ambilight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMBILIGHT_H
