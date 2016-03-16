/*
 * SharedCellObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedCellObjectTemplate.h"

#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../../system/iff/IffStream.h"

#include "../../../../swgforensics.h"

SharedCellObjectTemplate::SharedCellObjectTemplate(IffStream* str) :
	SharedObjectTemplate(str) {
}

SharedCellObjectTemplate::~SharedCellObjectTemplate() {
}

void SharedCellObjectTemplate::parseFileData(IffStream* iffStream) {
	/*iffStream->openChunk('PCNT');

	int variableCount = iffStream->getInt();

	iffStream->closeChunk('PCNT');

	for (int i = 0; i < variableCount; ++i) {
		Chunk* chunk = iffStream->openChunk();

		if (chunk == NULL)
			continue;

		if (chunk->getChunkID() == 'XXXX') {
			QString varName;
			chunk->getString(varName);

			parseVariableData(varName, chunk);
		} else {
			SWGForensics::instance->printToConsole("WTF AM I OPENING AGAIN");
		}

		iffStream->closeChunk();
	}*/
}

void SharedCellObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {

}

void SharedCellObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedCellObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
