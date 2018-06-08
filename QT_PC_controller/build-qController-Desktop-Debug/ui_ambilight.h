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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ambilight
{
public:

    void setupUi(QWidget *Ambilight)
    {
        if (Ambilight->objectName().isEmpty())
            Ambilight->setObjectName(QStringLiteral("Ambilight"));
        Ambilight->resize(400, 300);

        retranslateUi(Ambilight);

        QMetaObject::connectSlotsByName(Ambilight);
    } // setupUi

    void retranslateUi(QWidget *Ambilight)
    {
        Ambilight->setWindowTitle(QApplication::translate("Ambilight", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Ambilight: public Ui_Ambilight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMBILIGHT_H
