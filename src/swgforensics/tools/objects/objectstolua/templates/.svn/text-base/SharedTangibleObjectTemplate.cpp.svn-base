/*
 * SharedTangibleObjectTemplate.cpp
 *
 *  Created on: 21-feb-2009
 *      Author: TheAnswer
 */

#include "SharedTangibleObjectTemplate.h"

#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../../system/iff/IffStream.h"

#include "../../../../swgforensics.h"

SharedTangibleObjectTemplate::SharedTangibleObjectTemplate(IffStream* str) :
	SharedObjectTemplate(str) {
}

SharedTangibleObjectTemplate::~SharedTangibleObjectTemplate() {
	//std::cout << "DELETING SharedTangibleObjectTemplate\n";
}

void SharedTangibleObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedTangibleObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
	if (varName == "paletteColorCustomizationVariables") {
		paletteColorCustomizationVariables.parse(data);
		variables[varName] = &paletteColorCustomizationVariables;
	} else if (varName == "rangedIntCustomizationVariables") {
		rangedIntCustomizationVariables.parse(data);
		variables[varName] = &rangedIntCustomizationVariables;
	} else if (varName == "constStringCustomizationVariables") {
		uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();

		if (num != 0) {
			QString fileName = data->getIffStream()->getFileName().c_str();
			SWGForensics::instance->printToConsole("EUREKA found constStringCustomizationVariables" + fileName);
			SWGForensics::instance->runTraverse = false;
		}
	} else if (varName == "socketDestinations") {
		socketDestinations.parse(data);
		variables[varName] = &socketDestinations;
	} else if (varName == "structureFootprintFileName") {
		structureFootprintFileName.parse(data);
		variables[varName] = &structureFootprintFileName;
	} else if (varName == "useStructureFootprintOutline") {
		useStructureFootprintOutline.parse(data);
		variables[varName] = &useStructureFootprintOutline;
	} else if (varName == "targetable") {
		targetable.parse(data);
		variables[varName] = &targetable;
	} else if (varName == "certificationsRequired") {
		certificationsRequired.parse(data);
		variables[varName] = &certificationsRequired;
	} else if (varName == "customizationVariableMapping") {
		customizationVariableMapping.parse(data);
		variables[varName] = &customizationVariableMapping;
	}
}

void SharedTangibleObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedTangibleObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
