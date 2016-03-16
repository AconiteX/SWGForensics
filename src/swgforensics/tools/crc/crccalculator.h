#ifndef CRCCALCULATOR_H
#define CRCCALCULATOR_H

#include <QtGui/QWidget>
#include "ui_crccalculator.h"

class SWGForensics;

class CRCCalculator : public QWidget
{
    Q_OBJECT

public:
    CRCCalculator(SWGForensics* mainWindow, QWidget *parent = 0);
    ~CRCCalculator();

public slots:
    void calculateCRC();

private:
    Ui::CRCCalculatorClass ui;
    SWGForensics* mainWindow;
};

#endif // CRCCALCULATOR_H
