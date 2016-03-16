/********************************************************************************
** Form generated from reading UI file 'packetanalizer.ui'
**
** Created: Thu 10. Mar 23:22:41 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKETANALIZER_H
#define UI_PACKETANALIZER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PacketAnalizerClass
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *PacketAnalizerClass)
    {
        if (PacketAnalizerClass->objectName().isEmpty())
            PacketAnalizerClass->setObjectName(QString::fromUtf8("PacketAnalizerClass"));
        PacketAnalizerClass->resize(400, 300);
        pushButton = new QPushButton(PacketAnalizerClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(160, 130, 75, 23));

        retranslateUi(PacketAnalizerClass);

        QMetaObject::connectSlotsByName(PacketAnalizerClass);
    } // setupUi

    void retranslateUi(QWidget *PacketAnalizerClass)
    {
        PacketAnalizerClass->setWindowTitle(QApplication::translate("PacketAnalizerClass", "PacketAnalizer", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("PacketAnalizerClass", "Start", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PacketAnalizerClass: public Ui_PacketAnalizerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKETANALIZER_H
