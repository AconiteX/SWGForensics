/*
 * SharedCreatureObjectTemplate.cpp
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#include "SharedCreatureObjectTemplate.h"

SharedCreatureObjectTemplate::SharedCreatureObjectTemplate(IffStream* str) :
	SharedTangibleObjectTemplate(str) {
}

SharedCreatureObjectTemplate::~SharedCreatureObjectTemplate() {
}

void SharedCreatureObjectTemplate::parseFileData(IffStream* iffStream) {
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

void SharedCreatureObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
	if (varName == "gender") {
		gender.parse(data);
		variables[varName] = &gender;
	} else if (varName == "niche") {
		niche.parse(data);
		variables[varName] = &niche;
	} else if (varName == "species") {
		species.parse(data);
		variables[varName] = &species;
	} else if (varName == "race") {
		race.parse(data);
		variables[varName] = &race;
	} else if (varName == "acceleration") {
		acceleration.parse(data);
		variables[varName] = &acceleration;
	} else if (varName == "speed") {
		speed.parse(data);
		variables[varName] = &speed;
	} else if (varName == "turnRate") {
		turnRate.parse(data);
		variables[varName] = &turnRate;
	} else if (varName == "animationMapFilename") {
		animationMapFilename.parse(data);
		variables[varName] = &animationMapFilename;
	} else if (varName == "slopeModAngle") {
		slopeModAngle.parse(data);
		variables[varName] = &slopeModAngle;
	} else if (varName == "slopeModPercent") {
		slopeModPercent.parse(data);
		variables[varName] = &slopeModPercent;
	} else if (varName == "waterModPercent") {
		waterModPercent.parse(data);
		variables[varName] = &waterModPercent;
	} else if (varName == "stepHeight") {
		stepHeight.parse(data);
		variables[varName] = &stepHeight;
	} else if (varName == "collisionHeight") {
		collisionHeight.parse(data);
		variables[varName] = &collisionHeight;
	} else if (varName == "collisionRadius") {
		collisionRadius.parse(data);
		variables[varName] = &collisionRadius;
	} else if (varName == "movementDatatable") {
		movementDatatable.parse(data);
		variables[varName] = &movementDatatable;
	} else if (varName == "postureAlignToTerrain") {
		postureAlignToTerrain.parse(data);
		variables[varName] = &postureAlignToTerrain;
	} else if (varName == "swimHeight") {
		swimHeight.parse(data);
		variables[varName] = &swimHeight;
	} else if (varName == "warpTolerance") {
		warpTolerance.parse(data);
		variables[varName] = &warpTolerance;
	} else if (varName == "collisionOffsetX") {
		collisionOffsetX.parse(data);
		variables[varName] = &collisionOffsetX;
	} else if (varName == "collisionOffsetZ") {
		collisionOffsetZ.parse(data);
		variables[varName] = &collisionOffsetZ;
	} else if (varName == "collisionLength") {
		collisionLength.parse(data);
		variables[varName] = &collisionLength;
	} else if (varName == "cameraHeight") {
		cameraHeight.parse(data);
		variables[varName] = &cameraHeight;
	}
}

void SharedCreatureObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedCreatureObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}
