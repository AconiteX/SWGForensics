/*
 * DisassemblerEngine.h
 *
 *  Created on: 07-dic-2008
 *      Author: TheAnswer
 */

#ifndef DISASSEMBLERENGINE_H_
#define DISASSEMBLERENGINE_H_

extern "C" {
#include "../../../DisassemblerLib/disasm.h"
}

class DisassemblerEngine {
	t_disasm da;
	t_asmmodel am;

public:
	DisassemblerEngine();

	char* disassemble(const char* code, unsigned int baseAddress = 0x400000);

	unsigned int getSizeOfCommand(const char* code, unsigned int baseAddress = 0x400000);

	unsigned int findFirstInstruction(const char* code, unsigned int baseAddress, unsigned int curInstrAddr, int n);
};

#endif /* DISASSEMBLERENGINE_H_ */
