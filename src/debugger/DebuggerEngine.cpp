#include "DebuggerEngine.h"

#include "../swgforensics/processlist/processlist.h"
#include "DisassemblerEngine.h"
#include <QMessageBox>
#include <QTextStream>

DebuggerEngine::DebuggerEngine(SWGForensics* main) : QThread(), mutex(QMutex::Recursive) {
	processHandle 	= (HANDLE) INVALID_HANDLE_VALUE;
	threadHandle	= (HANDLE) INVALID_HANDLE_VALUE;

	engineInUse		= false;

	processSuspended = false;

	DebugSetProcessKillOnExit(false);

	debugProcessID = 0;
	debugProcessIDToOpen = 0;

	waitingForEvent = false;

	doRun = true;

	running = false;

	mainWindow = main;
	processListUi = new ProcessList(this);

	disassemblerEngine = new DisassemblerEngine();

	//readdBreakpoint = false;

	connectSignals();

	//LPTSTR szCmdline[] = _tcsdup(TEXT("\"C:\\Program Files\\MyApp\" -L -S"));
		//CreateProcess(NULL, szCmdline, /*...*/);
}

DebuggerEngine::~DebuggerEngine() {
	delete processListUi;
	processListUi = NULL;

	delete disassemblerEngine;
	disassemblerEngine = NULL;

	finish();
}

void DebuggerEngine::connectSignals() {
	connect(this, SIGNAL(outputDebugString(QString)), (QObject*)mainWindow, SLOT(printDebugString(QString)));
	connect(this, SIGNAL(successfulAttach()), (QObject*)mainWindow, SLOT(successfulAttach()));
	connect(this, SIGNAL(debuggerError(QString)), (QObject*)mainWindow, SLOT(showError(QString)));
	connect(this, SIGNAL(outputToConsole(QString)), (QObject*)mainWindow, SLOT(printToConsole(QString)));
	connect(this, SIGNAL(breakpointSignal(Breakpoint*)), (QObject*)mainWindow, SLOT(breakpointReached(Breakpoint*)));
}

void DebuggerEngine::clearBreakpoints(bool doLock) {
	QMutexLocker locker(&mutex);


	Breakpoint* breakpoint;

	while ((breakpoint = breakpointList.begin().value()) != NULL)
		removeBreakpoint(breakpoint->getAddress(), false);

}

bool DebuggerEngine::init() {
	QMutexLocker locker(&mutex);

	unsigned long processID;

	printProcessList(false);

	std::cout << "\nEnter processID to attach:";
	std::cin >> processID;

	if (!attachToProcess(processID, false)) {
		std::cout << "\nUnable to attach to process!\n";


		return false;
	} else
		std::cout << "Succesufully attached to process!\n";

	running = true;



	return true;
}

void DebuggerEngine::finish() {
	QMutexLocker locker(&mutex);

	if (!running) {
		return;
	}

	clearBreakpoints(false);

	closeProcessHandle(false);

	if (debugProcessID != 0) {
		if (!DebugActiveProcessStop(debugProcessID)) {
			DWORD error = GetLastError();

			QString err;
			QTextStream stream(&err);
			stream << "DebugActiveProcessStop() failed with error [0x" << hex << error << "]";

			emit debuggerError(err);
		}

		debugProcessID = 0;
	}

	running = false;

	emit outputToConsole("Debugger deattached...");

}

void DebuggerEngine::run() {
	/*if (!init())
		return;*/
	doRun = true;

	emit outputToConsole("Starting Debugger Thread...");

	if (debugProcessIDToOpen == 0) {
		emit debuggerError("No process specified.");
		return;
	}

	if (!attachToProcess(debugProcessIDToOpen)) {
		emit debuggerError("Unable to attach to process.");
		return;
	}

	emit successfulAttach();

	running = true;

	DWORD dwContinueStatus = DBG_CONTINUE;

	DEBUG_EVENT debugEvent;

	while (doRun) {
		if (WaitForDebugEvent(&debugEvent, 1000)) {
			setWaitingForEvent(true);

			processDebuggingEvent(debugEvent);

			// Resume executing the thread that reported the debugging event. .
			ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, dwContinueStatus);
		} else {
			DWORD error = GetLastError();

			if (error != 0x79)	{
				QString err;
				QTextStream stream(&err);
				stream << "WaitForDebugEvent() failed with error [0x" << hex << error << "]!";
				emit debuggerError(err);

				break;
			}
		}
	}

	setWaitingForEvent(false);

	finish();

	//exec();
}

void DebuggerEngine::stop() {
	QMutexLocker locker(&mutex);

	doRun = false;


}

bool DebuggerEngine::closeProcessHandle(bool doLock) {
	QMutexLocker locker(&mutex);

	if (engineInUse) {
		// are we in use?
		if (CloseHandle(processHandle)) {
			// yup, so close the process handle
			engineInUse = false;


			return true;
		}
	}


	return false;
}

bool DebuggerEngine::terminateProcess() {
	QMutexLocker locker(&mutex);

	if (engineInUse) {
		if (TerminateProcess(processHandle, (UINT) 0x0D1ED1E)) {
			CloseHandle(processHandle);
			engineInUse = false;


			return true;
		}
	}


	return false;
}


void DebuggerEngine::printProcessList(bool doLock) {
	QMutexLocker locker(&mutex);

	DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {

        return;
    }

    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
	char x;

	for (i = 0; i < cProcesses; ++i) {
        if (aProcesses[i] != 0)
            printProcessNameAndID(aProcesses[i], false);

		if ((i % 8) == 0 && (i != 0)) {
			std::cout << "\ncontinue? ";
			std::cin >> x;

			if (x == 'n') {

				return;
			}
		}
	}


}

void DebuggerEngine::showProcessList() {
	DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    processListUi->clearProcesses();

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
    	emit debuggerError("no processes found");
        return;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

	for (i = 0; i < cProcesses; ++i) {
        if (aProcesses[i] != 0) {
        	QString name;
        	getProcessNameAndID(aProcesses[i], name, false);

        	processListUi->addProcess(name, aProcesses[i]);
        }

	}

	processListUi->show();
}

void DebuggerEngine::printProcessNameAndID(DWORD processID, bool doLock) {
	QMutexLocker locker(&mutex);

	if (processID == 0) {

		return;
	}

	char szProcessName[MAX_PATH] = "unknown";

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess ) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(char));

    }

    // Print the process name and identifier.

    printf("%s  (PID: %u)\n", szProcessName, (unsigned int)processID);

    CloseHandle(hProcess);


}

void DebuggerEngine::getProcessNameAndID(DWORD processID, QString& returnString, bool doLock) {
	QMutexLocker locker(&mutex);

	if (processID == 0) {

		return;
	}

	char szProcessName[MAX_PATH] = "unknown";

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess ) {
        HMODULE hMod;
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(char));

    }

    // Print the process name and identifier.

    char text[100];

    sprintf(text, "%s  (PID: %u)", szProcessName, (unsigned int)processID);

    CloseHandle(hProcess);

    returnString = text;


}


bool DebuggerEngine::openProcess(char* processWindowTitle, bool doLock) {
	QMutexLocker locker(&mutex);

	HWND 	targetWindowHandle	= (HWND) -1;
	DWORD 	processId 			= 0xFFFFFFFF;
	//HANDLE 	WindowProcessId		= (HANDLE) INVALID_HANDLE_VALUE;

	if (engineInUse) {
		// we are already in use...

		return false;
	}

	targetWindowHandle = FindWindowA(NULL, processWindowTitle); 	// see if it exist

	if (targetWindowHandle) {
		// got the window handle...
		bool processIDSucces = GetWindowThreadProcessId(targetWindowHandle, &processId); //get a PROCESS number

		if (processIDSucces) {
			// we have a valid process id, now to open it...
			processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

			if (processHandle) {
				// process succesfully opened
				engineInUse = true;

				return true;
			 }
		}
	}



	return false;
}

bool DebuggerEngine::openProcess(DWORD processID, bool doLock) {
	QMutexLocker locker(&mutex);

	//HWND 	TargetWindowHandle	= (HWND) -1;
	DWORD 	ProcessId 			= processID;
	//HANDLE 	WindowProcessId		= (HANDLE) INVALID_HANDLE_VALUE;

	if (engineInUse) {
		// we are already in use...

		return false;
	}

		// we have a valid process id, now to open it...
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, ProcessId);

	if (processHandle) {
		// process succesfully opened
		engineInUse = true;

		return true;
	}

	emit debuggerError("Couldnt retrieve a valid process handle");



	return false;
}

bool DebuggerEngine::attachToProcess(DWORD processID, bool doLock) {
	QMutexLocker locker(&mutex);

	QString msg;
	QTextStream stream(&msg);

	stream << "Trying to attach to: " << processID;
	emit outputToConsole(msg);

	if (!openProcess(processID, false)) {

		return false;
	}

	engineInUse = DebugActiveProcess(processID);

	debugProcessID = processID;



	return engineInUse;
}

bool DebuggerEngine::addBreakpoint(unsigned long address, BreakpointHandler* handler, bool doLock) {
	if (breakpointList[address] != NULL)
		return false;

	QString msg;
	QTextStream stream(&msg);
	stream << "Trying to create breakpoint in: [0x" << hex << address << "]";
	//emit outputToConsole(msg);

	QMutexLocker locker(&mutex);

	if (!engineInUse) {

		return false;
	}

	suspendProcess(false);

	unsigned char oldBytes[20];
	unsigned char int3 = 0xCC;

	if (!readMemory(address, oldBytes, 20, false, false)) {
		emit debuggerError("Could not read memory for breakpoint creation!");
		awakeProcess(false);

		return false;
	}

	if (!writeMemory(address, &int3, 1, false, false)) {
		emit debuggerError("Could not write memory for breakpoint creation!");
		awakeProcess(false);

		return false;
	}

	QString msg2;
	QTextStream stream2(&msg2);
	stream2 << "Created breakpoint with oldData:" << hex << (unsigned short)oldBytes[0];
	//emit outputToConsole(msg2);

	Breakpoint* breakpoint = new Breakpoint(address, oldBytes, handler);
	breakpointList[address] = breakpoint;


	awakeProcess(false);



	return true;
}

void DebuggerEngine::processDebuggingEvent(DEBUG_EVENT debugEvent) {
	DWORD code = debugEvent.dwDebugEventCode;

	/*QString t;
	QTextStream inp(&t);

	inp << "caught debug event " << hex << code;
	emit outputToConsole(t);*/

	switch (debugEvent.dwDebugEventCode) {
	case EXCEPTION_DEBUG_EVENT:
		// Process the exception code. When handling
		// exceptions, remember to set the continuation
		// status parameter (dwContinueStatus). This value
		// is used by the ContinueDebugEvent function.

		switch(debugEvent.u.Exception.ExceptionRecord.ExceptionCode) {
		case EXCEPTION_ACCESS_VIOLATION:
			// First chance: Pass this on to the system.
			// Last chance: Display an appropriate error.
			break;

		case EXCEPTION_BREAKPOINT:
			// First chance: Display the current
			// instruction and register values.
			handleBreakpointEvent(debugEvent);
			break;

		case EXCEPTION_DATATYPE_MISALIGNMENT:
			// First chance: Pass this on to the system.
			// Last chance: Display an appropriate error.
			break;

		case EXCEPTION_SINGLE_STEP:
			// First chance: Update the display of the
			// current instruction and register values.
			break;

		case DBG_CONTROL_C:
			// First chance: Pass this on to the system.
			// Last chance: Display an appropriate error.
			break;

		default:
			// Handle other exceptions.
			break;
		}

		case CREATE_THREAD_DEBUG_EVENT:
			// As needed, examine or change the thread's registers
			// with the GetThreadContext and SetThreadContext functions;
			// and suspend and resume thread execution with the
			// SuspendThread and ResumeThread functions.

			//dwContinueStatus = OnCreateThreadDebugEvent(debugEvent);
			break;

		case CREATE_PROCESS_DEBUG_EVENT:
			// As needed, examine or change the registers of the
			// process's initial thread with the GetThreadContext and
			// SetThreadContext functions; read from and write to the
			// process's virtual memory with the ReadProcessMemory and
			// WriteProcessMemory functions; and suspend and resume
			// thread execution with the SuspendThread and ResumeThread
			// functions. Be sure to close the handle to the process image
			// file with CloseHandle.

			//dwContinueStatus = OnCreateProcessDebugEvent(debugEvent);
			handleCreateProcessDebugEvent(debugEvent);
			break;

		case EXIT_THREAD_DEBUG_EVENT:
			// Display the thread's exit code.

			//dwContinueStatus = OnExitThreadDebugEvent(debugEvent);
			break;

		case EXIT_PROCESS_DEBUG_EVENT:
			// Display the process's exit code.

			//dwContinueStatus = OnExitProcessDebugEvent(debugEvent);
			break;

		case LOAD_DLL_DEBUG_EVENT:
			// Read the debugging information included in the newly
			// loaded DLL. Be sure to close the handle to the loaded DLL
			// with CloseHandle.

			//dwContinueStatus = OnLoadDllDebugEvent(debugEvent);
			break;

		case UNLOAD_DLL_DEBUG_EVENT:
			// Display a message that the DLL has been unloaded.

			//dwContinueStatus = OnUnloadDllDebugEvent(debugEvent);
			break;

		case OUTPUT_DEBUG_STRING_EVENT:
			// Display the output debugging string.

			handleOutputDebugStringEvent(debugEvent);
			//dwContinueStatus = OnOutputDebugStringEvent(debugEvent);
			break;

		case RIP_EVENT:
			//dwContinueStatus = OnRipEvent(debugEvent);
			break;
	}
}

bool DebuggerEngine::handleCreateProcessDebugEvent(DEBUG_EVENT debugEvent) {
	emit processCreated();
}

bool DebuggerEngine::handleOutputDebugStringEvent(DEBUG_EVENT debugEvent) {
	QMutexLocker locker(&mutex);

	int size = debugEvent.u.DebugString.nDebugStringLength;
	LPSTR address = debugEvent.u.DebugString.lpDebugStringData;

	char text[size];

	if (readMemory((long unsigned int)address, text, size, false, false)) {
		QString line = text;



		line.remove("\n");

		emit outputDebugString(line);

		return true;
	}



	return false;
}

bool DebuggerEngine::handleBreakpointEvent(DEBUG_EVENT debugEvent) {
	QMutexLocker locker(&mutex);

	//emit outputToConsole("Breakpoint reached!");

	bool exit = false;
	//int test;

	HANDLE	debugProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, debugEvent.dwProcessId);
	HANDLE	debugThreadHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, debugEvent.dwThreadId);

	unsigned long breakpointLocation = 0;

	CONTEXT context;

	context.ContextFlags = CONTEXT_FULL;
	GetThreadContext(debugThreadHandle, &context);

	breakpointLocation = context.Eip - 1;

	Breakpoint* breakpoint = breakpointList[breakpointLocation];

	if (breakpoint != NULL) {
		Breakpoint* origBp = breakpoint->getOriginalBreakpoint();

		removeBreakpoint(breakpointLocation, false);

		if (origBp != NULL) {
			addBreakpoint(origBp->getAddress(), origBp->getBreakpointHandler(), false);
		} else {
			breakpoint->setContext(&context);

			emit breakpointSignal(breakpoint);

			breakpoint->callHandler();

			if (breakpoint->readdBreakpoint())
				readdBreakpoint(breakpoint);
			else
				delete breakpoint;
		}

		--context.Eip;

		exit = true;
	}

	SetThreadContext(debugThreadHandle, &context);
	CloseHandle(debugProcessHandle);
	CloseHandle(debugThreadHandle);



	return exit;
}

void DebuggerEngine::readdBreakpoint(Breakpoint* breakpoint) {
	unsigned char* code = breakpoint->getFullOriginalData();

	unsigned long breakpointLocation = breakpoint->getAddress();

	if (breakpointList[breakpointLocation] != NULL)
		return;

	int size = disassemblerEngine->getSizeOfCommand((const char*)code);
	unsigned long address = breakpointLocation + size;

	if (!engineInUse)
		return;

	suspendProcess(false);

	unsigned char oldBytes[20];
	unsigned char int3 = 0xCC;

	if (!readMemory(address, oldBytes, 20, false, false)) {
		emit debuggerError("Could not read memory for breakpoint creation!");
		awakeProcess(false);
		return;
	}

	if (!writeMemory(address, &int3, 1, false, false)) {
		emit debuggerError("Could not write memory for breakpoint creation!");
		awakeProcess(false);
		return;
	}

	/*QString msg2;
	QTextStream stream2(&msg2);
	stream2 << "Created breakpoint with oldData:" << hex << (unsigned short)oldBytes[0];
	emit outputToConsole(msg2);*/

	Breakpoint* tempBp = new Breakpoint(breakpoint, oldBytes);

	breakpointList[address] = tempBp;

	awakeProcess(false);
}


bool DebuggerEngine::removeBreakpoint(unsigned long address, bool doLock) {
	QMutexLocker locker(&mutex);

	if (!engineInUse) {

		return false;
	}

	Breakpoint* breakpoint = breakpointList[address];

	if (breakpoint == NULL) {

		return false;
	}

	unsigned char oldData = breakpoint->getOriginalData();

	writeMemory(address, &oldData, 1, false, false);

	breakpointList.erase(breakpointList.find(address));

	//delete breakpoint;



	return true;
}

bool DebuggerEngine::writeMemory(unsigned long lpBaseAddress, LPVOID lpBuffer, DWORD nSize, bool suspProcess, bool doLock) {
	QMutexLocker locker(&mutex);

	bool successCode = false;

	if (engineInUse) {
		// are we in use
		if (processHandle) {
			// do we have a process handle
			DWORD BytesWritten = 0;

			if (suspProcess)
				suspendProcess(false);

			if ((WriteProcessMemory(processHandle, (LPVOID)lpBaseAddress, lpBuffer, nSize, &BytesWritten)
					&& BytesWritten == nSize)) {
				// write was successful
				// flush the instruction cache (for safety)
				FlushInstructionCache(processHandle, (LPVOID)lpBaseAddress, nSize);
				successCode = true;
			}

			if (suspProcess)
				awakeProcess(false);
		}
	}



	return successCode;
}

void* DebuggerEngine::allocateMemory(int size, bool suspProcess) {
	QMutexLocker locker(&mutex);

	void* address = NULL;

	if (suspProcess)
		suspendProcess(false);

	address = VirtualAllocEx(processHandle, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (suspProcess)
		awakeProcess(false);



	return address;
}

void DebuggerEngine::freeMemory(void* address, int size, bool suspProcess) {
	QMutexLocker locker(&mutex);

	if (suspProcess)
		suspendProcess(false);

	VirtualFreeEx(processHandle, address, size, MEM_RELEASE);

	if (suspProcess)
		awakeProcess(false);


}

void DebuggerEngine::suspendProcess(bool doLock) {
	QMutexLocker locker(&mutex);

	if (!processSuspended) {
		if (SuspendThread(processHandle) != (DWORD) -1) {
			processSuspended = TRUE;
		}
	}


}

void DebuggerEngine::awakeProcess(bool doLock) {
	QMutexLocker locker(&mutex);

	if (processSuspended) {
		ResumeThread(processHandle);
		processSuspended = false;
	}


}

bool DebuggerEngine::readMemory(unsigned long lpBaseAddress, LPVOID lpBuffer, DWORD nSize, bool suspProcess, bool doLock) {
	QMutexLocker locker(&mutex);

	bool SuccessCode = false;

	if (engineInUse) {
		if (processHandle) {
			DWORD BytesRead = 0;

			if (suspProcess)
				suspendProcess(false);

			if ((ReadProcessMemory(processHandle, (LPVOID)lpBaseAddress, lpBuffer, nSize, &BytesRead)
					&& BytesRead == nSize)) {
				SuccessCode = true;
			}

			if (suspProcess)
				awakeProcess(false);
		}
	}



	return SuccessCode;
}

char* DebuggerEngine::disassemble(const char* code, unsigned int baseAddress) {
	return disassemblerEngine->disassemble((char*)code, baseAddress);
}
