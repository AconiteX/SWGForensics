/*
 * SharedDraftSchematicObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedDraftSchematicObjectTemplate.h"

SharedDraftSchematicObjectTemplate::SharedDraftSchematicObjectTemplate(IffStream* str) :
	SharedIntangibleObjectTemplate(str) {
}

SharedDraftSchematicObjectTemplate::~SharedDraftSchematicObjectTemplate() {
}

void SharedDraftSchematicObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedDraftSchematicObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
}

void SharedDraftSchematicObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedDraftSchematicObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
