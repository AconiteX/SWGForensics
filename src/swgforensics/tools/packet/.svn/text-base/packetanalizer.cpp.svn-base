#include "packetanalizer.h"

#include "src/debugger/DebuggerEngine.h"
#include "src/swgforensics/swgforensics.h"

#include <QTextStream>

PacketAnalizer::PacketAnalizer(SWGForensics* mainwin, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	mainWindow = mainwin;
	debuggerEngine = mainWindow->getDebuggerEngine();

	running = false;

	connectSignals();
}

PacketAnalizer::~PacketAnalizer() {

}

void PacketAnalizer::connectSignals() {
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(startAnalizing()));
	connect(this, SIGNAL(outputToConsole(QString)), (QObject*)mainWindow, SLOT(printToConsole(QString)));
}

void PacketAnalizer::handleBreakpoint(Breakpoint* breakpoint) {
	switch (breakpoint->getAddress()) {
	case 0x0118B06F:
		handleByteRead(breakpoint);
		break;
	case 0x00439FDC:
		handleAsciiRead(breakpoint);
		break;
	case 0x0051BD79:
		handleStartingPacketParsing(breakpoint);
		break;
	}
}

void PacketAnalizer::handleStartingPacketParsing(Breakpoint* breakpoint) {
	CONTEXT* context = breakpoint->getContext();

	QString test = tr("ecx = %1").arg(context->Ecx);

	breakpoint->setReadd(true);

	emit outputToConsole(test);
}

void PacketAnalizer::startAnalizing() {
	if (running) {
		stopAnalizing();
		return;
	}

	/*bool res = debuggerEngine->addBreakpoint(0x0118B06F, this);
	bool res2 = debuggerEngine->addBreakpoint(0x00439FDC, this);*/

	bool res, res2;
	res = res2 = debuggerEngine->addBreakpoint(0x0051BD79, this);

	/*0051BD79*/

	if (res && res2)
		emit outputToConsole("Packet Analizer started.");
	else {
		emit outputToConsole("Error starting Packet Analizer");
		return;
	}

	running = true;

	ui.pushButton->setText(QApplication::translate("PacketAnalizerClass", "Stop", 0, QApplication::UnicodeUTF8));
}

void PacketAnalizer::stopAnalizing() {
	/*bool res = debuggerEngine->removeBreakpoint(0x0118B06F);
	bool res2 = debuggerEngine->removeBreakpoint(0x00439FDC);*/
	bool res, res2;
	res = res2 = debuggerEngine->removeBreakpoint(0x0051BD79);

	if (res && res2)
		emit outputToConsole("Packet Analizer stopped.");
	else {
		emit outputToConsole("Error while attempting to stop Packet Analizer.");
		return;
	}

	running = false;

	ui.pushButton->setText(QApplication::translate("PacketAnalizerClass", "Start", 0, QApplication::UnicodeUTF8));
}

void PacketAnalizer::handleByteRead(Breakpoint* breakpoint) {
	// called in the debugger engine thread;
	CONTEXT* context = breakpoint->getContext();

	QString test = tr("ecx = %1").arg(context->Ecx);
	//emit outputToConsole(test);

	unsigned char* code = breakpoint->getFullOriginalData();

	/*char* disasm = debuggerEngine->disassemble((const char*)code);

		QString instr(disasm);
		emit outputToConsole(instr);*/

	unsigned long packetAddress = context->Esi + context->Eax;
	unsigned int size = context->Ecx;
	unsigned char data[size];

	if (!debuggerEngine->readMemory(packetAddress, data, size, false, false)) {
		emit outputToConsole("couldnt read memory");
		return;
	}

	/*if ((size == 4) && (*(unsigned int*)data == 0x13642A6D))
			emit outputToConsole("received chat");*/

	/*if (size == 1) {
		QString text;
		QTextStream streamer(&text);

		streamer << (char*)data;
		emit outputToConsole(text);
	}*/
}

void PacketAnalizer::handleAsciiRead(Breakpoint* breakpoint) {
	CONTEXT* context = breakpoint->getContext();

	int asciiSize = context->Ecx;
	unsigned long packetAddress = context->Esi;

	char ascii[asciiSize + 1];

	if (!debuggerEngine->readMemory(packetAddress, ascii, asciiSize, false, false)) {
		emit outputToConsole("couldnt read memory");
		return;
	}

	ascii[asciiSize] = 0;

	QString text;
	QTextStream streamer(&text);

	streamer << (char*)ascii;
	emit outputToConsole(text);
}


