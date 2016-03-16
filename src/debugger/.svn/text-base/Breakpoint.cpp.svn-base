/*
 * Breakpoing.cpp
 *
 *  Created on: 07-dic-2008
 *      Author: TheAnswer
 */

#include "Breakpoint.h"

Breakpoint::Breakpoint(unsigned long address, unsigned char* originalData, BreakpointHandler* hand) {
	memcpy(Breakpoint::originalData, originalData, 20);

	Breakpoint::address = address;

	Breakpoint::handler = hand;

	originalBreakpoint = NULL;

	readd = false;

	init();
}

Breakpoint::Breakpoint(Breakpoint* bp, unsigned char* originalData) {
	memcpy(Breakpoint::originalData, originalData, 20);

	address = bp->getAddress();

	handler = bp->getBreakpointHandler();

	originalBreakpoint = bp;

	readd = bp->readdBreakpoint();

	init();
}

Breakpoint::~Breakpoint() {
	free(context);
}

void Breakpoint::init() {
	keepBreakpoint = false;

	context = NULL;
}

void Breakpoint::setContext(CONTEXT* ctxt) {
	context = (CONTEXT*)malloc(sizeof(CONTEXT));
	memcpy(context, ctxt, sizeof(CONTEXT));
}
