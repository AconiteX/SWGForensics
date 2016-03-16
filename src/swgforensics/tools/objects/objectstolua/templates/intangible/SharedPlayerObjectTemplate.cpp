/*
 * SharedPlayerObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedPlayerObjectTemplate.h"

SharedPlayerObjectTemplate::SharedPlayerObjectTemplate(IffStream* str) :
	SharedIntangibleObjectTemplate(str) {
}

SharedPlayerObjectTemplate::~SharedPlayerObjectTemplate() {
}

void SharedPlayerObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedPlayerObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedPlayerObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedPlayerObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}

