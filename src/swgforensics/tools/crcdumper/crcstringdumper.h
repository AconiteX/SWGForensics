#ifndef CRCSTRINGDUMPER_H
#define CRCSTRINGDUMPER_H

#include <QtGui/QWidget>
#include "ui_crcstringdumper.h"

#include "src/debugger/Breakpoint.h"

class DebuggerEngine;
class SWGForensics;

class crcstringdumper : public QWidget, public BreakpointHandler {
    Q_OBJECT

public:
    crcstringdumper(SWGForensics* mainwin, QWidget *parent = 0);
    ~crcstringdumper();

public slots:
	void startDumpingStrings();
	void stopDumpingStrings();
    void handleBreakpoint(Breakpoint* breakpoint);

signals:
   	void outputToConsole(const QString& str);

private:
    Ui::crcstringdumperClass ui;
    SWGForensics* mainWindow;
    DebuggerEngine* debuggerEngine;

    bool running;
};

#endif // CRCSTRINGDUMPER_H
