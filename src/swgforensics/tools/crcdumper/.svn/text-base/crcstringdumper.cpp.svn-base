#include "crcstringdumper.h"

#include "src/debugger/DebuggerEngine.h"
#include "src/swgforensics/swgforensics.h"

#include <QTextStream>

crcstringdumper::crcstringdumper(SWGForensics* mainwin, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	mainWindow = mainwin;

	debuggerEngine = mainWindow->getDebuggerEngine();

	running = false;
}

crcstringdumper::~crcstringdumper() {

}

void crcstringdumper::handleBreakpoint(Breakpoint* breakpoint) {

}

void crcstringdumper::stopDumpingStrings() {

}

void crcstringdumper::startDumpingStrings() {
	/*if (running) {
		stopDumpingStrings();
		return;
	}

	bool res = debuggerEngine->addBreakpoint(0x00AA47C9, this);

	if (res)
		emit outputToConsole("CRC String Dumper started.");*/
}
