/*
 * SharedObjectTemplate.cpp
 *
 *  Created on: 19-feb-2009
 *      Author: TheAnswer
 */

#include "SharedObjectTemplate.h"
#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../swgforensics.h"

SharedObjectTemplate::SharedObjectTemplate(IffStream* str)
	: Template(str) {

}

SharedObjectTemplate::~SharedObjectTemplate() {
	/*QMap<QString, Variable*>::const_iterator i;

	for (i = variables.constBegin(); i != variables.constEnd(); ++i)
		delete i.value();*/
}

void SharedObjectTemplate::parseFileData(IffStream* iffStream) {
	iffStream->openChunk('PCNT');

	int variableCount = iffStream->getInt();

	iffStream->closeChunk('PCNT');

	for (int i = 0; i < variableCount; ++i) {
	//while (iffStream->getRemainingSubChunksNumber() > 0) {
		Chunk* chunk = iffStream->openChunk('XXXX');

		if (chunk == NULL)
			continue;

		QString varName;
		iffStream->getString(varName);

		//std::cout << "parsing wtf shit:[" << varName.toStdString() << "]\n";
		parseVariableData(varName, chunk);

		iffStream->closeChunk();
	}
}

void SharedObjectTemplate::parseVariableData(const QString& varName, Chunk* data) {
	if (varName == "objectName") {
		objectName.parse(data);
		variables[varName] = &objectName;
	} else if (varName == "detailedDescription") {
		detailedDescription.parse(data);
		variables[varName] = &detailedDescription;
	} else if (varName == "lookAtText") {
		lookAtText.parse(data);
		variables[varName] = &lookAtText;
	} else if (varName == "snapToTerrain") {
		snapToTerrain.parse(data);
		variables[varName] = &snapToTerrain;
	} else if (varName == "containerType") {
		containerType.parse(data);
		variables[varName] = &containerType;
	} else if (varName == "containerVolumeLimit") {
		containerVolumeLimit.parse(data);
		variables[varName] = &containerVolumeLimit;
	} else if (varName == "tintPallete") {
		tintPallete.parse(data);
		variables[varName] = &tintPallete;
	} else if (varName == "slotDescriptorFilename") {
		slotDescriptorFilename.parse(data);
		//QString newName = "slotDescriptors";
		variables[varName] = &slotDescriptorFilename;
	} else if (varName == "arrangementDescriptorFilename") {
		arrangementDescriptorFilename.parse(data);
		//QString newName = "arrangementDescriptors";
		variables[varName] = &arrangementDescriptorFilename;
	} else if (varName == "appearanceFilename") {
		appearanceFilename.parse(data);
		variables[varName] = &appearanceFilename;
	} else if (varName == "portalLayoutFilename") {
		portalLayoutFilename.parse(data);
		variables[varName] = &portalLayoutFilename;
		QString newName = "totalCellNumber";
		totalCellNumber = (portalLayoutFilename.getTotalCellNumber());
		variables[newName] = &totalCellNumber;
	} else if (varName == "clientDataFile") {
		clientDataFile.parse(data);
		variables[varName] = &clientDataFile;
	} else if (varName == "collisionMaterialFlags") {
		collisionMaterialFlags.parse(data);
		variables[varName] = &collisionMaterialFlags;
	} else if (varName == "collisionMaterialPassFlags") {
		collisionMaterialPassFlags.parse(data);
		variables[varName] = &collisionMaterialPassFlags;
	} else if (varName == "collisionMaterialBlockFlags") {
		collisionMaterialBlockFlags.parse(data);
		variables[varName] = &collisionMaterialBlockFlags;
	} else if (varName == "collisionActionFlags") {
		collisionActionFlags.parse(data);
		variables[varName] = &collisionActionFlags;
	} else if (varName == "collisionActionPassFlags") {
		collisionActionPassFlags.parse(data);
		variables[varName] = &collisionActionPassFlags;
	} else if (varName == "collisionActionBlockFlags") {
		collisionActionBlockFlags.parse(data);
		variables[varName] = &collisionActionBlockFlags;
	} else if (varName == "scale") {
		scale.parse(data);
		variables[varName] = &scale;
	} else if (varName == "gameObjectType") {
		gameObjectType.parse(data);
		clientGameObjectType = gameObjectType.get();
		variables[varName] = &gameObjectType;
		variables["clientGameObjectType"] = &clientGameObjectType;
	} else if (varName == "sendToClient") {
		sendToClient.parse(data);
		variables[varName] = &sendToClient;
	} else if (varName == "scaleThresholdBeforeExtentTest") {
		scaleThresholdBeforeExtentTest.parse(data);
		variables[varName] = &scaleThresholdBeforeExtentTest;
	} else if (varName == "clearFloraRadius") {
		clearFloraRadius.parse(data);
		variables[varName] = &clearFloraRadius;
	} else if (varName == "surfaceType") {
		surfaceType.parse(data);
		variables[varName] = &surfaceType;
	} else if (varName == "noBuildRadius") {
		noBuildRadius.parse(data);
		variables[varName] = &noBuildRadius;
	} else if (varName == "onlyVisibleInTools") {
		onlyVisibleInTools.parse(data);
		variables[varName] = &onlyVisibleInTools;
	} else if (varName == "locationReservationRadius") {
		locationReservationRadius.parse(data);
		variables[varName] = &locationReservationRadius;
	}
}

void SharedObjectTemplate::printVariables(Ui::ObjectsToLuaClass* ui) {
	ui->listWidget->clear();

	QMap<QString, Param*>::const_iterator i;

	for (i = variables.constBegin(); i != variables.constEnd(); ++i)
		ui->listWidget->addItem(i.key());

	/*QString crc;
	QTextStream stream(&crc);
	stream << "ObjectCRC:[" << objectCRC << "]";
	SWGForensics::instance->printToConsole(crc);*/

	/*ui->listWidget->addItem("objectName");
	ui->listWidget->addItem("detailedDescription");
	ui->listWidget->addItem("lookAtText");
	ui->listWidget->addItem("snapToTerrain");
	ui->listWidget->addItem("containerType");
	ui->listWidget->addItem("containerVolumeLimit");
	ui->listWidget->addItem("tintPallete");
	ui->listWidget->addItem("slotDescriptorFilename");
	ui->listWidget->addItem("arrangementDescriptorFilename");
	ui->listWidget->addItem("appearanceFilename");
	ui->listWidget->addItem("portalLayoutFilename");
	ui->listWidget->addItem("clientDataFile");
	ui->listWidget->addItem("collisionMaterialFlags");
	ui->listWidget->addItem("collisionMaterialPassFlags");
	ui->listWidget->addItem("scale");
	ui->listWidget->addItem("collisionMaterialBlockFlags");
	ui->listWidget->addItem("collisionActionFlags");
	ui->listWidget->addItem("collisionActionPassFlags");
	ui->listWidget->addItem("collisionActionBlockFlags");
	ui->listWidget->addItem("gameObjectType");
	ui->listWidget->addItem("sendToClient");
	ui->listWidget->addItem("scaleThresholdBeforeExtentTest");
	ui->listWidget->addItem("clearFloraRadius");
	ui->listWidget->addItem("surfaceType");
	ui->listWidget->addItem("noBuildRadius");
	ui->listWidget->addItem("onlyVisibleInTools");
	ui->listWidget->addItem("locationReservationRadius");*/
}

void SharedObjectTemplate::printVariable(const QString& varName, Ui::ObjectsToLuaClass* ui) {
	QString val;

	if (variables.contains(varName)) {
		//val = variables[varName]->toString();

		Param* param = variables[varName];
		val = param->toString();
	}

	/*if (varName == "objectName") {
		val = objectName.toString();
	} else if (varName == "detailedDescription") {
		val = detailedDescription.toString();
	} else if (varName == "lookAtText") {
		val = lookAtText.toString();
	} else if (varName == "snapToTerrain") {
		val = snapToTerrain.toString();
	} else if (varName == "containerType") {
		val = containerType.toString();
	} else if (varName == "containerVolumeLimit") {
		val = containerVolumeLimit.toString();
	} else if (varName == "tintPallete") {
		val = tintPallete.toString();
	} else if (varName == "slotDescriptorFilename") {
		val = slotDescriptorFilename.toString();
	} else if (varName == "arrangementDescriptorFilename") {
		val = arrangementDescriptorFilename.toString();
	} else if (varName == "appearanceFilename") {
		val = appearanceFilename.toString();
	} else if (varName == "portalLayoutFilename") {
		val = portalLayoutFilename.toString();
	} else if (varName == "clientDataFile") {
		val = clientDataFile.toString();
	} else if (varName == "collisionMaterialFlags") {
		val = collisionMaterialFlags.toString();
	} else if (varName == "collisionMaterialPassFlags") {
		val = collisionMaterialPassFlags.toString();
	} else if (varName == "collisionMaterialBlockFlags") {
		val = collisionMaterialBlockFlags.toString();
	} else if (varName == "collisionActionFlags") {
		val = collisionActionFlags.toString();
	} else if (varName == "collisionActionPassFlags") {
		val = collisionActionPassFlags.toString();
	} else if (varName == "collisionActionBlockFlags") {
		val = collisionActionBlockFlags.toString();
	} else if (varName == "scale") {
		val = scale.toString();
	} else if (varName == "gameObjectType") {
		val = gameObjectType.toString();
	} else if (varName == "sendToClient") {
		val = sendToClient.toString();
	} else if (varName == "scaleThresholdBeforeExtentTest") {
		val = scaleThresholdBeforeExtentTest.toString();
	} else if (varName == "clearFloraRadius") {
		val = clearFloraRadius.toString();
	} else if (varName == "surfaceType") {
		val = surfaceType.toString();
	} else if (varName == "noBuildRadius") {
		val = noBuildRadius.toString();
	} else if (varName == "onlyVisibleInTools") {
		val = onlyVisibleInTools.toString();
	} else if (varName == "locationReservationRadius") {
		val = locationReservationRadius.toString();
	}*/

	ui->textBrowser->clear();
	ui->textBrowser->append(val);
}

void SharedObjectTemplate::toLua(QTextStream& buffer) {
	//writeLuaHeader(buffer);

	buffer << endl;

	buffer << luaObjectName << " = SharedObjectTemplate:new {" << endl;

	variablesToLua(buffer);

	buffer << "}" << endl << endl << "ObjectTemplates:addClientTemplate(" << luaObjectName << ", \"" << fileName << "\")" << endl;
}

void SharedObjectTemplate::variablesToLua(QTextStream& buffer) {
	QMap<QString, Param*>::const_iterator i;

	QString value;
	QString name = "a";

	buffer << "\tclientTemplateFileName = \"" << fileName << "\"" << endl;

	buffer << "\t--Data below here is deprecated and loaded from the tres, keeping for easy lookups\n";

	buffer << "--[[\n";

	for (i = variables.constBegin(); i != variables.constEnd(); ++i) {
		if (name[0] != i.key()[0])
			buffer << endl;

		name = i.key();
		value = i.value()->toString();

		buffer << "\t" << name << " = " << value;

		//if ((i + 1) != variables.constEnd())
			buffer << ",";

		buffer << endl;
	}

	buffer << endl;
	buffer << "\tclientObjectCRC = " << objectCRC << ",";
	buffer << endl;


	buffer << "\tderivedFromTemplates = {";
	//QVector<QString>::const_iterator a;

	for (int a = 0; a < loadedDerivedFiles.size(); ++a) {
		buffer << "\"" << loadedDerivedFiles.at(a) << "\"";

		if (a + 1 < loadedDerivedFiles.size())
			buffer << ", ";
	}

	buffer << "}" << endl;

	buffer << "]]";

	buffer << endl;

}

