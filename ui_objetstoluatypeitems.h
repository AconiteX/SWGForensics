/********************************************************************************
** Form generated from reading ui file 'objetstoluatypeitems.ui'
**
** Created: Sat 18. Apr 03:03:36 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_OBJETSTOLUATYPEITEMS_H
#define UI_OBJETSTOLUATYPEITEMS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_objetstoluaTypeItemsClass
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;

    void setupUi(QWidget *objetstoluaTypeItemsClass)
    {
    if (objetstoluaTypeItemsClass->objectName().isEmpty())
        objetstoluaTypeItemsClass->setObjectName(QString::fromUtf8("objetstoluaTypeItemsClass"));
    objetstoluaTypeItemsClass->resize(657, 561);
    horizontalLayout = new QHBoxLayout(objetstoluaTypeItemsClass);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setMargin(11);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    treeView = new QTreeView(objetstoluaTypeItemsClass);
    treeView->setObjectName(QString::fromUtf8("treeView"));

    horizontalLayout->addWidget(treeView);


    retranslateUi(objetstoluaTypeItemsClass);

    QMetaObject::connectSlotsByName(objetstoluaTypeItemsClass);
    } // setupUi

    void retranslateUi(QWidget *objetstoluaTypeItemsClass)
    {
    objetstoluaTypeItemsClass->setWindowTitle(QApplication::translate("objetstoluaTypeItemsClass", "objetstoluaTypeItems", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(objetstoluaTypeItemsClass);
    } // retranslateUi

};

namespace Ui {
    class objetstoluaTypeItemsClass: public Ui_objetstoluaTypeItemsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJETSTOLUATYPEITEMS_H
