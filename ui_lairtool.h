/********************************************************************************
** Form generated from reading UI file 'lairtool.ui'
**
** Created: Thu 31. Mar 15:58:53 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAIRTOOL_H
#define UI_LAIRTOOL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LairToolClass
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *LairToolClass)
    {
        if (LairToolClass->objectName().isEmpty())
            LairToolClass->setObjectName(QString::fromUtf8("LairToolClass"));
        LairToolClass->resize(400, 300);
        pushButton = new QPushButton(LairToolClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(110, 120, 161, 23));

        retranslateUi(LairToolClass);

        QMetaObject::connectSlotsByName(LairToolClass);
    } // setupUi

    void retranslateUi(QWidget *LairToolClass)
    {
        LairToolClass->setWindowTitle(QApplication::translate("LairToolClass", "LairTool", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("LairToolClass", "Generate Lair scripts", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LairToolClass: public Ui_LairToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAIRTOOL_H
