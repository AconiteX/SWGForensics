#ifndef DEBUGGERENGINE_H_
#define DEBUGGERENGINE_H_

#include "system.h"

#include "Breakpoint.h"

#include <QString>
#include <QtGui/QMainWindow>
#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMap>

class ProcessList;
class SWGForensics;
class DisassemblerEngine;

class DebuggerEngine : public QThread {
	Q_OBJECT

	QMutex mutex;

	HANDLE processHandle;
	HANDLE threadHandle;

	bool engineInUse;
	bool processSuspended;

	DWORD debugProcessID;
	DWORD debugProcessIDToOpen;

	QMap<unsigned long, Breakpoint*> breakpointList;

	DisassemblerEngine* disassemblerEngine;

	bool waitingForEvent;
	bool doRun;
	bool running;

	//bool readdBreakpoint;

	SWGForensics* mainWindow;
	ProcessList* processListUi;

private:
	bool init();
	void finish();

	void connectSignals();

	void processDebuggingEvent(DEBUG_EVENT debugEvent);

	bool handleBreakpointEvent(DEBUG_EVENT debugEvent);
	bool handleOutputDebugStringEvent(DEBUG_EVENT debugEvent);
	bool handleCreateProcessDebugEvent(DEBUG_EVENT debugEvent);

	void readdBreakpoint(Breakpoint* breakpoint);

	/*inline void lock(bool doLock = true) {
		if (doLock)
			mutex.lock();
	}

	inline void unlock(bool doLock = true) {
		if (doLock)
			mutex.unlock();
	}*/

public slots:
	//

signals:
	void successfulAttach();
	void outputDebugString(const QString& string);
	void outputToConsole(const QString& string);

	void debuggerError(const QString& msg);

	void processCreated();

	void breakpointSignal(Breakpoint* bp);

public:
	DebuggerEngine(SWGForensics* main);
	virtual ~DebuggerEngine();

	void printProcessList(bool doLock = true);
	void printProcessNameAndID(DWORD processID, bool doLock = true);

	void getProcessNameAndID(DWORD processID, QString& returnString, bool doLock = true);

	void showProcessList();

	bool openProcess(char* processWindowTitle, bool doLock = true);
	bool openProcess(DWORD processID, bool doLock = true);

	bool attachToProcess(DWORD processID, bool doLock = true);

	bool closeProcessHandle(bool doLock = true);
	void clearBreakpoints(bool doLock = true);

	void run();
	void stop();

	bool addBreakpoint(unsigned long address, BreakpointHandler* handler = NULL, bool doLock = true);
	bool removeBreakpoint(unsigned long address, bool doLock = true);

	bool terminateProcess();

	bool writeMemory(unsigned long lpBaseAddress, LPVOID lpBuffer, DWORD nSize, bool suspProcess = true, bool doLock = true);
	bool readMemory(unsigned long lpBaseAddress, LPVOID lpBuffer, DWORD nSize, bool suspProcess = true, bool doLock = true);

	void* allocateMemory(int size, bool suspProcess = true);
	void freeMemory(void* address, int size, bool suspProcess = true);

	void suspendProcess(bool doLock = true);
	void awakeProcess(bool doLock = true);

	char* disassemble(const char* code, unsigned int baseAddress = 0x400000);

	inline HANDLE getProcessHandle() {
		return processHandle;
	}

	inline void setProcessToOpen(DWORD id) {
		QMutexLocker locker(&mutex);

		debugProcessIDToOpen = id;


	}

	inline void setWaitingForEvent(bool val) {
		QMutexLocker locker(&mutex);

		waitingForEvent = val;


	}

	inline bool isWaitingForEvent() {
		bool ret;

		QMutexLocker locker(&mutex);

		ret = waitingForEvent;



		return ret;
	}

	/*inline bool isRunning() {
		bool ret;

		lock();

		ret = running;

		unlock();

		return ret;
	}*/
};


#endif /*DEBUGGERENGINE_H_*/
