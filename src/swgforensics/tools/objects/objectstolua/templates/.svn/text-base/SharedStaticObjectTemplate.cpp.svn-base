/*
 * SharedStaticObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedStaticObjectTemplate.h"

#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../../system/iff/IffStream.h"

#include "../../../../swgforensics.h"

SharedStaticObjectTemplate::SharedStaticObjectTemplate(IffStream* str) :
	SharedBuildingObjectTemplate(str) {
}

SharedStaticObjectTemplate::~SharedStaticObjectTemplate() {
}

void SharedStaticObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedStaticObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {

}

void SharedStaticObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedStaticObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
