/*
 * SharedGuildObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedGuildObjectTemplate.h"

SharedGuildObjectTemplate::SharedGuildObjectTemplate(IffStream* str) :
	SharedUniverseObjectTemplate(str) {
}

SharedGuildObjectTemplate::~SharedGuildObjectTemplate() {
}

void SharedGuildObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedGuildObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedGuildObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedGuildObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}

