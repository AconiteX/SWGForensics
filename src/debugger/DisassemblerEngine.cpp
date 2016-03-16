/*
 * DisassemblerEngine.cpp
 *
 *  Created on: 07-dic-2008
 *      Author: TheAnswer
 */

extern "C" {
#define STRICT
#define MAINPROG
}

#include "DisassemblerEngine.h"

DisassemblerEngine::DisassemblerEngine() {

}

char* DisassemblerEngine::disassemble(const char* code, unsigned int baseAddress) {
	Disasm((char*)code, sizeof(code) - 1, baseAddress, &da, DISASM_CODE);

	return da.result;
}

unsigned int DisassemblerEngine::getSizeOfCommand(const char* code, unsigned int baseAddress) {
	return Disasm((char*)code, sizeof(code) - 1, baseAddress, &da, DISASM_SIZE);
}

unsigned int DisassemblerEngine::findFirstInstruction(const char* code, unsigned int baseAddress, unsigned int curInstrAddr, int n) {
	return Disassembleforward((char*) code, baseAddress, sizeof(code) - 1, curInstrAddr, n);
}
