#ifndef BREAKPOINT_H_
#define BREAKPOINT_H_

#include <windows.h>
class Breakpoint;

class BreakpointHandler {
public:
	virtual void handleBreakpoint(Breakpoint* bp) = 0;
};

class Breakpoint {
	unsigned long address;

	BreakpointHandler* handler;

	bool keepBreakpoint;

	unsigned char originalData[20];

	CONTEXT* context;

	Breakpoint* originalBreakpoint;

	bool readd;

public:
	Breakpoint(unsigned long address, unsigned char* originalData, BreakpointHandler* hand = NULL);

	Breakpoint(Breakpoint* bp, unsigned char* originalData);
	~Breakpoint();

	void init();

	void setContext(CONTEXT* ctxt);

	inline Breakpoint* getOriginalBreakpoint() {
		return originalBreakpoint;
	}

	inline CONTEXT* getContext() {
		return context;
	}

	inline void callHandler() {
		if (handler != NULL)
			handler->handleBreakpoint(this);
	}

	inline void setKeeping(bool val) {
		keepBreakpoint = val;
	}

	inline bool keepBreakoint() {
		return keepBreakpoint;
	}

	inline unsigned long getAddress() {
		return address;
	}

	inline unsigned char getOriginalData() {
		return originalData[0];
	}

	inline unsigned char* getFullOriginalData() {
		return originalData;
	}

	inline BreakpointHandler* getBreakpointHandler() {
		return handler;
	}

	inline bool readdBreakpoint() {
		return readd;
	}

	inline bool setReadd(bool val) {
		readd = val;
	}

};

#endif /*BREAKPOINT_H_*/
