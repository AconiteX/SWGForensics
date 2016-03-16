/********************************************************************************
** Form generated from reading UI file 'crcstringdumper.ui'
**
** Created: Thu 10. Mar 23:22:41 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRCSTRINGDUMPER_H
#define UI_CRCSTRINGDUMPER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_crcstringdumperClass
{
public:

    void setupUi(QWidget *crcstringdumperClass)
    {
        if (crcstringdumperClass->objectName().isEmpty())
            crcstringdumperClass->setObjectName(QString::fromUtf8("crcstringdumperClass"));
        crcstringdumperClass->resize(400, 300);

        retranslateUi(crcstringdumperClass);

        QMetaObject::connectSlotsByName(crcstringdumperClass);
    } // setupUi

    void retranslateUi(QWidget *crcstringdumperClass)
    {
        crcstringdumperClass->setWindowTitle(QApplication::translate("crcstringdumperClass", "crcstringdumper", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class crcstringdumperClass: public Ui_crcstringdumperClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRCSTRINGDUMPER_H
