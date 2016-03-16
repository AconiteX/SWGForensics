/*
 * SharedBattlefieldMarkerObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedBattlefieldMarkerObjectTemplate.h"

SharedBattlefieldMarkerObjectTemplate::SharedBattlefieldMarkerObjectTemplate(IffStream* str) :
	SharedTangibleObjectTemplate(str) {
}

SharedBattlefieldMarkerObjectTemplate::~SharedBattlefieldMarkerObjectTemplate() {
}

void SharedBattlefieldMarkerObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedBattlefieldMarkerObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedBattlefieldMarkerObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedBattlefieldMarkerObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
