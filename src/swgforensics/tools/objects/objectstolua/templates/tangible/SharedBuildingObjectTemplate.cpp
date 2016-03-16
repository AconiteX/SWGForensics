/*
 * SharedBuildingObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedBuildingObjectTemplate.h"

SharedBuildingObjectTemplate::SharedBuildingObjectTemplate(IffStream* str) :
	SharedTangibleObjectTemplate(str) {
}

SharedBuildingObjectTemplate::~SharedBuildingObjectTemplate() {
}

void SharedBuildingObjectTemplate::parseFileData(IffStream* iffStream) {
	iffStream->openChunk('PCNT');

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
	}
}

void SharedBuildingObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
	if (varName == "terrainModificationFileName") {
		terrainModificationFileName.parse(data);
		variables[varName] = &terrainModificationFileName;
	} else if (varName == "interiorLayoutFileName") {
		interiorLayoutFileName.parse(data);
		variables[varName] = &interiorLayoutFileName;
	}
}

void SharedBuildingObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedBuildingObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
