#include "swgforensics.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <QFileDialog>

#include <QtGui/QTextBrowser>
#include <QtGui/QScrollBar>

#include "processlist/processlist.h"
#include "../debugger/DebuggerEngine.h"
#include "tools/packet/PacketAnalizer.h"
#include "tools/objects/objectstolua/ObjectsToLua.h"
#include "tools/crc/crccalculator.h"
#include "tools/terrain/terrainanalizer.h"
#include "tools/floor/FloorMeshAnalizer.h"
#include "tools/lair/LairTool.h"

SWGForensics* SWGForensics::instance = NULL;

SWGForensics::SWGForensics(QApplication* app, QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	mainApplication = app;
	autoScrollDebugLog = true;
	debuggerEngine = new DebuggerEngine(this);
	packetAnalizer = new PacketAnalizer(this);
	objectsToLua = new ObjectsToLua(this);
	crcCalculator = new CRCCalculator(this);
	terrainAnalizer = new TerrainAnalizer(this);
	floorMeshAnalizer = new FloorMeshAnalizer();
	lairTool = new LairTool();

	runTraverse = true;

	printToConsole("SWGForensics v0.01");
	/*QString te;
	QTextStream stream(&te);

	stream << sizeof(TestClass);
	printToConsole(te);*/

	connectSignals();

	/*unsigned int test = 'STOT';
	test = htonl(test);

	char type[5];
	memcpy(type, &test, 4);
	type[4] = 0;

	std::string tesT((char*)&test, 4);
	QString var = tesT.c_str();
	//var = tesT;

	printToConsole(var);*/

	instance = this;
}

SWGForensics::~SWGForensics() {
	debuggerEngine->stop();
	debuggerEngine->wait();

	delete debuggerEngine;
	debuggerEngine = NULL;

	delete packetAnalizer;
	packetAnalizer = NULL;
}

void SWGForensics::setDebuggerActions(bool value) {
	ui.actionAttach_to_process->setEnabled(!value);
	ui.actionDeattach_from_process->setEnabled(value);
	ui.actionAdd_Breakpoint->setEnabled(value);
	ui.actionRead_Memory->setEnabled(value);
	ui.actionRemove_Breakpoint->setEnabled(value);
	ui.actionSearch_Memory->setEnabled(value);
	ui.actionWrite_Memory->setEnabled(value);
}

void SWGForensics::breakpointReached(Breakpoint* breakpoint) {
}

void SWGForensics::connectSignals() {
	connect(ui.actionQuit, SIGNAL(triggered()), mainApplication, SLOT(quit()));
	connect(ui.actionSave_Debug_Log, SIGNAL(triggered()), this, SLOT(saveDebugLogAs()));
	connect(ui.actionAttach_to_process, SIGNAL(triggered()), this, SLOT(showProcessList()));
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(autoScrollTriggered(int)));
	connect(ui.actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui.actionDeattach_from_process, SIGNAL(triggered()), this, SLOT(deattachFromProcess()));
	connect(ui.actionShow_internal_console, SIGNAL(toggled(bool)), this, SLOT(triggerConsole(bool)));
	connect(ui.textBrowser_2->verticalScrollBar(), SIGNAL(sliderPressed()), this, SLOT(disableAutoScroll()));
	connect(ui.actionAdd_Breakpoint, SIGNAL(triggered()), this, SLOT(addBreakpoint()));
	connect(ui.actionPacket_Struct_Analizer, SIGNAL(triggered()), packetAnalizer, SLOT(show()));
	connect(ui.actionIff_Object_Templates, SIGNAL(triggered()), objectsToLua, SLOT(show()));
	connect(ui.actionCRC_Calculator, SIGNAL(triggered()), crcCalculator, SLOT(show()));
	connect(ui.actionTerrain_Analizer, SIGNAL(triggered()), terrainAnalizer, SLOT(show()));
	connect(ui.actionFloor_Mesh_Analizer, SIGNAL(triggered()), floorMeshAnalizer, SLOT(show()));
	connect(ui.actionLair_Tool, SIGNAL(triggered()), lairTool, SLOT(show()));
}

void SWGForensics::showPacketAnalizer() {
	packetAnalizer->show();
}

void SWGForensics::showStatusBarMessage(const QString& msg, int timeout) {
	statusBar()->showMessage(msg, timeout);
}

bool SWGForensics::saveDebugLogFile(const QString& fileName) {
	QFile file(fileName);

	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("SDI"),
				tr("Cannot write file %1:\n%2.")
				.arg(fileName)
				.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);

	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << ui.textBrowser_2->toPlainText();

	QApplication::restoreOverrideCursor();

	//setCurrentFile(fileName);
	printToConsole("File saved");
	return true;
}

void SWGForensics::autoScrollTriggered(int state) {
	switch (state) {
	case (Qt::Unchecked):
		autoScrollDebugLog = false;
		break;
	case (Qt::Checked):
		autoScrollDebugLog = true;
		break;
	default:
		break;
	}
}

void SWGForensics::disableAutoScroll() {
	if (autoScrollDebugLog) {
		autoScrollDebugLog = false;

		ui.checkBox->setChecked(false);
	}
}

void SWGForensics::triggerConsole(bool state) {
	if (state) {
		ui.textBrowser->show();
	} else {
		ui.textBrowser->close();
	}
}

void SWGForensics::showProcessList() {
	debuggerEngine->showProcessList();
}

void SWGForensics::showAbout() {
	QMessageBox::about(this, "SWGForensics", "SWGForensics v0.01 by TheAnswer");
}

void SWGForensics::printDebugString(const QString& str) {
	/*QString newStr = str;

	newStr.remove("\n");*/
	ui.textBrowser_2->append(str);

	if (autoScrollDebugLog)
		ui.textBrowser_2->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
}

void SWGForensics::printToConsole(const QString& str) {
	ui.textBrowser->append(str);
	ui.textBrowser->verticalScrollBar()->triggerAction(QAbstractSlider::SliderToMaximum);
	showStatusBarMessage(str, 2000);
}

void SWGForensics::successfulAttach() {
	printToConsole("Successfully attached to process...");
	ui.textBrowser_2->append("Waiting for Debug Strings...");

	setDebuggerActions(true);
}

void SWGForensics::deattachFromProcess() {
	if (ui.actionDeattach_from_process->isEnabled())
		debuggerEngine->stop();

	setDebuggerActions(false);
}

void SWGForensics::showError(const QString& msg) {
	printToConsole(msg);
	QMessageBox::warning(this, "Error", msg);
}

bool SWGForensics::saveDebugLogAs() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Debug Log"), "debuglog.txt");

	if (fileName.isEmpty())
		return false;

	return saveDebugLogFile(fileName);
}

void SWGForensics::addBreakpoint() {
	/*debuggerEngine->addBreakpoint(0x00B5DF51);
	printToConsole("breakpoint added");*/
}

uint32 SWGForensics::hashCode(const char* str, int len) {
	uint32 CRC = 0xFFFFFFFF;

	for (short counter = 0; counter < len; counter++)
		CRC = crctable[str[counter] ^ (CRC >> 24)] ^ (CRC << 8);

	return ~CRC;

}

uint32 SWGForensics::hashCode(const QString& str) {
	return hashCode(str.toStdString().c_str(), str.size());
}
