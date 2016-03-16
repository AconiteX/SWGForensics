#ifndef PACKETANALIZER_H
#define PACKETANALIZER_H

#include <QtGui/QWidget>
#include "ui_packetanalizer.h"

#include "src/debugger/Breakpoint.h"

class DebuggerEngine;
class SWGForensics;

class PacketAnalizer : public QWidget, public BreakpointHandler {
    Q_OBJECT

public:
    PacketAnalizer(SWGForensics* mainwin, QWidget *parent = 0);
    ~PacketAnalizer();

public slots:
	void startAnalizing();
	void stopAnalizing();
    void handleBreakpoint(Breakpoint* breakpoint);

signals:
	void outputToConsole(const QString& str);

private:
    Ui::PacketAnalizerClass ui;
    DebuggerEngine* debuggerEngine;
    SWGForensics* mainWindow;
    bool running;

    void connectSignals();

    void handleAsciiRead(Breakpoint* breakpoint);
    void handleByteRead(Breakpoint* breakpoint);
    void handleStartingPacketParsing(Breakpoint* breakpoint);
};

#endif // PACKETANALIZER_H
