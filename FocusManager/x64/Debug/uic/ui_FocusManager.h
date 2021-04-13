/********************************************************************************
** Form generated from reading UI file 'FocusManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOCUSMANAGER_H
#define UI_FOCUSMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FocusManagerClass
{
public:

    void setupUi(QWidget *FocusManagerClass)
    {
        if (FocusManagerClass->objectName().isEmpty())
            FocusManagerClass->setObjectName(QString::fromUtf8("FocusManagerClass"));
        FocusManagerClass->resize(600, 400);

        retranslateUi(FocusManagerClass);

        QMetaObject::connectSlotsByName(FocusManagerClass);
    } // setupUi

    void retranslateUi(QWidget *FocusManagerClass)
    {
        FocusManagerClass->setWindowTitle(QCoreApplication::translate("FocusManagerClass", "FocusManager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FocusManagerClass: public Ui_FocusManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOCUSMANAGER_H
