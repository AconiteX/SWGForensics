/*
 * SharedWeaponObjectTemplate.cpp
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#include "SharedWeaponObjectTemplate.h"
#include "../../../../../swgforensics.h"

SharedWeaponObjectTemplate::SharedWeaponObjectTemplate(IffStream* str) :
	SharedTangibleObjectTemplate(str) {
}

SharedWeaponObjectTemplate::~SharedWeaponObjectTemplate() {
}

void SharedWeaponObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedWeaponObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
	if (varName == "weaponEffect") {
		weaponEffect.parse(data);
		variables[varName] = &weaponEffect;
	} else if (varName == "weaponEffectIndex") {
		weaponEffectIndex.parse(data);
		variables[varName] = &weaponEffectIndex;
	} else if (varName == "attackType") {
		attackType.parse(data);
		variables[varName] = &attackType;
	}
}

void SharedWeaponObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedWeaponObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
