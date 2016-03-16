#ifndef LAIRTOOL_H
#define LAIRTOOL_H

#include <QtGui/QWidget>
#include "ui_lairtool.h"

class LairTool : public QWidget {
    Q_OBJECT

public:
    LairTool(QWidget *parent = 0);
    ~LairTool();

public slots:
	void generateLuaScripts();

private:
    Ui::LairToolClass ui;
};

#endif // LAIRTOOL_H
