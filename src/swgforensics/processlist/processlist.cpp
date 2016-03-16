#include "processlist.h"
#include <QErrorMessage>
#include <QTextStream>
#include <QMessageBox>

ProcessList::ProcessList(DebuggerEngine* engine, QWidget *parent): QWidget(parent) {
	ui.setupUi(this);

	debuggerEngine = engine;

	connectSignals();
}

ProcessList::~ProcessList() {

}

void ProcessList::connectSignals() {
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
		                          this,  SLOT(selectedProcess(QListWidgetItem*)));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(refresh()));
	//connect(ui.plainTextEdit, SIGNAL(textChanged()), this, SLOT(updateSearchString()));
}

void ProcessList::addProcess(const QString& name, int id) {
	processes.insert(name, id);

	ui.listWidget->addItem(name);
}

void ProcessList::clearProcesses() {
	processes.clear();
	ui.listWidget->clear();
}

void ProcessList::updateSearchString() {
	/*QString text = ui.plainTextEdit->toPlainText();

	QList<QListWidgetItem*> items = ui.listWidget->findItems (text, Qt::MatchContains);

	if (items.count() != 0) {
		QListWidgetItem* item = items.at(0);

		ui.listWidget->setCurrentItem(item);
	}*/
}

void ProcessList::refresh() {
	clearProcesses();

	debuggerEngine->showProcessList();
}

void ProcessList::selectedProcess(QListWidgetItem* item) {
	int id = processes.value(item->text());

	close();

	QApplication::setOverrideCursor(Qt::WaitCursor);

	debuggerEngine->setProcessToOpen(id);
	debuggerEngine->start();

	QApplication::restoreOverrideCursor();
}
