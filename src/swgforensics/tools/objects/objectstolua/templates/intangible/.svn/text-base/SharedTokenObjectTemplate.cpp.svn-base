/*
 * SharedTokenObjectTemplate.cpp
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#include "SharedTokenObjectTemplate.h"

SharedTokenObjectTemplate::SharedTokenObjectTemplate(IffStream* str) :
	SharedIntangibleObjectTemplate(str) {
}

SharedTokenObjectTemplate::~SharedTokenObjectTemplate() {
}

void SharedTokenObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedTokenObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedTokenObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedTokenObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
