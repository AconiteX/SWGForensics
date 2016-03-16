/*
 * SharedResourceContainerObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedResourceContainerObjectTemplate.h"

SharedResourceContainerObjectTemplate::SharedResourceContainerObjectTemplate(IffStream* str) :
	SharedTangibleObjectTemplate(str) {
}

SharedResourceContainerObjectTemplate::~SharedResourceContainerObjectTemplate() {
}

void SharedResourceContainerObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedResourceContainerObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedResourceContainerObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedResourceContainerObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
