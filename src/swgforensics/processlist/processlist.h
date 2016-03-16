#ifndef PROCESSLIST_H
#define PROCESSLIST_H

#include <QtGui/QWidget>
#include "ui_processlist.h"

#include <QVector>
#include <QtGui/QMainWindow>

#include "../../debugger/DebuggerEngine.h"

class ProcessList : public QWidget
{
    Q_OBJECT

public:
    ProcessList(DebuggerEngine* debugger, QWidget *parent = 0);
    ~ProcessList();

private:
    Ui::ProcessListClass ui;

    DebuggerEngine* debuggerEngine;
    QMap<QString, int> processes;

protected:
	void addProcess(const QString& name, int id);
	void clearProcesses();

	void connectSignals();

	friend class DebuggerEngine;

public slots:
	void selectedProcess(QListWidgetItem* item);
	void refresh();

	void updateSearchString();

};

#endif // PROCESSLIST_H
