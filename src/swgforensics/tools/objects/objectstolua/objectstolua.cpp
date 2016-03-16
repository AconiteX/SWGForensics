#include "objectstolua.h"

#include "../../../../system/iff/IffStream.h"
#include "../../../../system/iff/chunk/Chunk.h"
#include "../../../../system/iff/exceptions.h"

#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

#include "../../../swgforensics.h"

#include "floormesh/FloorMesh.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/SharedTangibleObjectTemplate.h"
#include "templates/tangible/SharedWeaponObjectTemplate.h"
#include "templates/tangible/SharedCreatureObjectTemplate.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "templates/tangible/SharedResourceContainerObjectTemplate.h"
#include "templates/tangible/SharedInstallationObjectTemplate.h"
#include "templates/tangible/SharedFactoryObjectTemplate.h"
#include "templates/tangible/SharedBuildingObjectTemplate.h"
#include "templates/tangible/SharedBattlefieldMarkerObjectTemplate.h"
#include "templates/tangible/SharedCountingObjectTemplate.h"

#include "templates/SharedIntangibleObjectTemplate.h"
#include "templates/intangible/SharedDraftSchematicObjectTemplate.h"
#include "templates/intangible/SharedManufactureSchematicObjectTemplate.h"
#include "templates/intangible/SharedWaypointObjectTemplate.h"
#include "templates/intangible/SharedPlayerObjectTemplate.h"
#include "templates/intangible/SharedMissionObjectTemplate.h"
#include "templates/intangible/SharedConstructionContractObjectTemplate.h"
#include "templates/intangible/SharedMissionDataObjectTemplate.h"
#include "templates/intangible/SharedMissionListEntryObjectTemplate.h"
#include "templates/intangible/SharedTokenObjectTemplate.h"

#include "templates/SharedUniverseObjectTemplate.h"
#include "templates/universe/SharedGuildObjectTemplate.h"
#include "templates/universe/SharedGroupObjectTemplate.h"
#include "templates/universe/SharedJediManagerTemplate.h"

#include "templates/SharedStaticObjectTemplate.h"
#include "templates/SharedCellObjectTemplate.h"

ObjectsToLua::ObjectsToLua(SWGForensics* mainWin, QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);

	openedTemplate = NULL;
	mainWindow = mainWin;

	numberOfFilesOpened = 0;

	maxRows = 0;

	currentRow = 0;

	connectSignals();
}

ObjectsToLua::~ObjectsToLua() {
	/*delete fileStream;
	fileStream = NULL;*/
}

void ObjectsToLua::connectSignals() {
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openObjectIffTemplate()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(convertToLuaDir()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(openFloorMesh()));
	connect(ui.listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
			                          this,  SLOT(selectedVariable(QListWidgetItem*)));
}

void ObjectsToLua::openFloorMesh() {
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isEmpty())
		return;

	FloorMesh* mesh = new FloorMesh(fileName);
	mesh->printToConsole();

	delete mesh;
}

bool ObjectsToLua::convertToLuaDir() {
	QDir dirName(QString(SWGTRESDIRECTORY) + "object");

	QApplication::setOverrideCursor(Qt::WaitCursor);

	openObjectIffTemplateDir(dirName);

	for (int i = 0; i < inheritance.size(); ++i)
		mainWindow->printToConsole(inheritance[i]);

	QFile* currentLuaFile = new QFile(dirName.absolutePath() + "/allobjects.lua");
	currentLuaFile->open(QIODevice::WriteOnly);
	currentLuaFile->setTextModeEnabled(true);

	QString runFiles;
	QTextStream stream(&runFiles);

	for (int i = 0; i < objectLuas.size(); ++i) {
		stream << "includeFile(\"" << objectLuas[i] << "\")\n";
		//mainWindow->printToConsole(objectLuas[i]);
	}

	currentLuaFile->write(runFiles.toAscii());
	currentLuaFile->close();
	delete currentLuaFile;

	QString files;
	QTextStream numFiles(&files);
	numFiles << numberOfFilesOpened;
	mainWindow->printToConsole("opened " + files + " files");

	QApplication::restoreOverrideCursor();
}

bool ObjectsToLua::openDir() {
	//QDir dirName = QFileDialog::getExistingDirectory(this);
	QDir dirName(QString(SWGTRESDIRECTORY) + "object");

	QApplication::setOverrideCursor(Qt::WaitCursor);

	openObjectIffTemplateDir(dirName);

	/*for (int i = 0; i < inheritance.size(); ++i)
		mainWindow->printToConsole(inheritance[i]);

	QFile* currentLuaFile = new QFile(dirName.absolutePath() + "/allobjects.lua");
	currentLuaFile->open(QIODevice::WriteOnly);
	currentLuaFile->setTextModeEnabled(true);

	QString runFiles;
	QTextStream stream(&runFiles);

	for (int i = 0; i < objectLuas.size(); ++i) {
		stream << "includeFile(\"" << objectLuas[i] << "\")\n";
		//mainWindow->printToConsole(objectLuas[i]);
	}

	currentLuaFile->write(runFiles.toAscii());
	currentLuaFile->close();
	delete currentLuaFile;*/

	/*QString fileName = "containerTypes.csv";

	QFile* file = new QFile(fileName);
	file->open(QIODevice::WriteOnly);
	file->setTextModeEnabled(true);

	QString fileContents;
	QTextStream fileStream(&fileContents);

	QMap<unsigned int, QStringList*>::const_iterator i;

	for (i = containerTypes.constBegin(); i != containerTypes.constEnd(); ++i) {
		uint32 type = i.key();

		fileStream << "0x" << hex << type << ";";

		QStringList* list = i.value();

		if (maxRows < list->size())
			maxRows = list->size();
	}

	fileStream << "\n";

	for (currentRow = 0; currentRow < maxRows; ++currentRow) {
		QMap<unsigned int, QStringList*>::const_iterator j;

		for (j = containerTypes.constBegin(); j != containerTypes.constEnd(); ++j) {
			QStringList* list = j.value();

			if (currentRow < list->size()) {
				fileStream << list->at(currentRow);
			}

			fileStream << ";";
		}

		fileStream << "\n";
	}

	file->write(fileContents.toAscii());
	file->close();
	delete file;*/


	/*QMap<unsigned int, QStringList*>::const_iterator i;

	for (i = objectTypes.constBegin(); i != objectTypes.constEnd(); ++i) {
		uint32 type = i.key();

		QString fileName;
		QTextStream fileNameStream(&fileName);

		fileNameStream << "types/0x" << hex << type << ".txt";

		QFile* file = new QFile(fileName);
		file->open(QIODevice::WriteOnly);
		file->setTextModeEnabled(true);

		QStringList* list = i.value();

		for (int j = 0; j < list->size(); ++j) {
			QString filename = list->at(j);
			filename += "\n";

			file->write(filename.toAscii());
		}

		file->close();
		delete file;

	}*/

	//mainWindow->printToConsole(oTypes);

	QString files;
	QTextStream numFiles(&files);
	numFiles << numberOfFilesOpened;
	mainWindow->printToConsole("opened " + files + " files");

	QApplication::restoreOverrideCursor();

	return true;
}

bool ObjectsToLua::openObjectIffTemplateDir(QDir dirName) {
	if (!SWGForensics::instance->runTraverse)
		return true;
	//QDir dirName = QFileDialog::getExistingDirectory(this);
	//dirName.setFilter(QDir::AllDirs);
	dirName.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);

	QStringList strlist = dirName.entryList();

	for (int i = 0; i < strlist.size(); ++i) {
		QString file = strlist.at(i);

		//QString directory = dirName.absolutePath();
		QString newDirectory = dirName.absolutePath();
		newDirectory.append("\\");
		newDirectory.append(file);

		openObjectIffTemplateDir(newDirectory);

		//mainWindow->printToConsole(file);
	}

	QString newLuaFile = dirName.absolutePath() + "/objects.lua";

	QFile* currentLuaFile = new QFile(newLuaFile);
	currentLuaFile->open(QIODevice::WriteOnly);
	currentLuaFile->setTextModeEnabled(true);

	/*for (int i = 0; i < strlist.size(); ++i) {
		QString directory = strlist.at(i);

		QString fullDir = dirName.absolutePath();
		fullDir.append("/objects.lua");
	}*/

	dirName.setFilter(QDir::Files);
	strlist = dirName.entryList();

	newLuaFile.remove(SWGTRESDIRECTORY);
	objectLuas.append(newLuaFile);

	QString header;
	QTextStream headerStream(&header);

	LuaWriter::writeLuaHeader(headerStream);
	currentLuaFile->write(header.toAscii());

	for (int i = 0; i < strlist.size(); ++i) {
		++numberOfFilesOpened;
		QString file = strlist.at(i);

		if (file.indexOf(".lua") != -1)
			continue;

		QString openFile = dirName.absolutePath();
		openFile.append("/");
		openFile.append(file);

		IffStream* fileStream = NULL;

		//QString fileName = "D:/swg tres/object/building/player/shared_player_city_capitol_corellia_style_01.iff";

		try {
			fileStream = new IffStream(openFile.toStdString());
		} catch (...) {
			mainWindow->printToConsole("invalid file " + openFile);
			//currentLuaFile->close();
			continue;
		}

		currentInheritance.clear();
		openedTemplate = loadObjectVariables(fileStream, NULL);

		if (!inheritance.contains(currentInheritance))
			inheritance.append(currentInheritance);

		if (!SWGForensics::instance->runTraverse)
			return true;

		if (openedTemplate != NULL) {

			IntegerParam* param = (IntegerParam*) ((SharedObjectTemplate*)openedTemplate)->getVariable("gameObjectType");
			if (param != NULL) {
				uint32 type = param->getValue();
				QString name = openedTemplate->getFileName();

				if (objectTypes.contains(type)) {
					QStringList* list = objectTypes[type];
					list->append(name);
				} else {
					QStringList* list = new QStringList();
					list->append(name);

					objectTypes[type] = list;
				}
			}

			IntegerParam* containerType = (IntegerParam*) ((SharedObjectTemplate*)openedTemplate)->getVariable("containerType");

			if (containerType != NULL) {
				uint32 type = containerType->getValue();
				QString name = openedTemplate->getFileName();

				if (containerTypes.contains(type)) {
					QStringList* list = containerTypes[type];
					list->append(name);
				} else {
					QStringList* list = new QStringList();
					list->append(name);

					containerTypes[type] = list;
				}
			}

			//openedTemplate->printVariables(&ui);

			QString luaTest;
			QTextStream luaStream(&luaTest);

			openedTemplate->toLua(luaStream);

			if (currentLuaFile != NULL)
				currentLuaFile->write(luaTest.toAscii());
		}

		delete fileStream;
		delete openedTemplate;
		openedTemplate = NULL;

		//mainWindow->printToConsole(file);
	}

	currentLuaFile->close();
	delete currentLuaFile;

	return true;
}

bool ObjectsToLua::openObjectIffTemplate() {
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isEmpty())
		return false;

	IffStream* fileStream = NULL;

	//QString fileName = "D:/swg tres/object/building/general/shared_newbie_hall.iff";

	try {
		fileStream = new IffStream(fileName.toStdString());
	} catch (...) {
		//mainWindow->printToConsole("invalid file " + fileName);
		return false;
	}

	currentInheritance.clear();
	openedTemplate = loadObjectVariables(fileStream, NULL);

	//mainWindow->printToConsole(currentInheritance);

	if (openedTemplate != NULL) {
		openedTemplate->printVariables(&ui);

		QString luaTest;
		QTextStream luaStream(&luaTest);

		openedTemplate->toLua(luaStream);

		/*if (currentLuaFile != NULL)
			currentLuaFile->write(luaTest.toAscii());*/

		//mainWindow->printToConsole(luaTest);
	}

	return true;
}

void ObjectsToLua::selectedVariable(QListWidgetItem* item) {
	QString var = item->text();

	openedTemplate->printVariable(var, &ui);
}

void ObjectsToLua::loadDerv(IffStream* stream, Template* previousTemplate) {
	//mainWindow->printToConsole("opening derv");

	stream->openForm('DERV');

	Chunk* chunk = stream->openChunk('XXXX');

	QString file;
	chunk->getString(file);

	//mainWindow->printToConsole(file);

	if (previousTemplate != NULL && previousTemplate->hasLoadedDerivedFile(file)) {
		stream->closeChunk();

		stream->closeForm('DERV');

		return;
	}

	QString trePath = SWGTRESDIRECTORY;

	QString fullPath = trePath + file;

	IffStream* newStream;// = new IffStream(fullPath.toStdString());

	try {
		newStream = new IffStream(fullPath.toStdString());
	} catch (...) {
		//mainWindow->printToConsole("invalid file " + fullPath);

		stream->closeChunk();
		stream->closeForm('DERV');
		return;
	}

	loadObjectVariables(newStream, previousTemplate);

	delete newStream;

	stream->closeChunk();

	stream->closeForm('DERV');

	if (previousTemplate != NULL)
		previousTemplate->addLoadedDerivedFile(file);
}

SharedObjectTemplate* ObjectsToLua::parseSHOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedObjectTemplate(iffStream);

	iffStream->openForm('SHOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	iffStream->openForm(derv);

	try {
		((SharedObjectTemplate*)previousTemplate)->parseFileData(iffStream);
	} catch (Exception& e) {
		QString msg;
		msg += "exception caught parsing file data ->";
		msg += e.getMessage().c_str();

		mainWindow->printToConsole(msg);
	}

	iffStream->closeForm(derv);

	iffStream->closeForm('SHOT');

	return (SharedObjectTemplate*)previousTemplate;
}

SharedTangibleObjectTemplate* ObjectsToLua::parseSTOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedTangibleObjectTemplate(iffStream);

	iffStream->openForm('STOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SSHP') {
			iffStream->openForm('SSHP');

			iffStream->closeForm('SSHP');
			//previousTemplate = new SharedShipObjectTemplate(iffStream);
		} else if (derv == 'SHOT') {
			parseSHOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
				try {
					((SharedTangibleObjectTemplate*)previousTemplate)->parseFileData(iffStream);
				} catch (Exception& e) {
					QString msg;
					msg += "exception caught parsing file data ->";
					msg += e.getMessage().c_str();
					msg += "of file:";
					msg += iffStream->getFileName().c_str();

					mainWindow->printToConsole(msg);
				}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('STOT');

	return (SharedTangibleObjectTemplate*)previousTemplate;
}

SharedWeaponObjectTemplate* ObjectsToLua::parseSWOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedWeaponObjectTemplate(iffStream);

	iffStream->openForm('SWOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedWeaponObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SWOT');

	return (SharedWeaponObjectTemplate*)previousTemplate;
}

SharedIntangibleObjectTemplate* ObjectsToLua::parseSITN(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedIntangibleObjectTemplate(iffStream);

	iffStream->openForm('SITN');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SHOT') {
			parseSHOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedIntangibleObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SITN');

	return (SharedIntangibleObjectTemplate*)previousTemplate;
}

SharedUniverseObjectTemplate* ObjectsToLua::parseSUNI(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedUniverseObjectTemplate(iffStream);

	iffStream->openForm('SUNI');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SHOT') {
			parseSHOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedUniverseObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SUNI');

	return (SharedUniverseObjectTemplate*)previousTemplate;
}

SharedStaticObjectTemplate* ObjectsToLua::parseSTAT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedStaticObjectTemplate(iffStream);

	iffStream->openForm('STAT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SHOT') {
			parseSHOT(iffStream, previousTemplate);
		} /*else if (derv == 'SBOT') {
			parseSBOT(iffStream, previousTemplate);
		}*/ else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedStaticObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('STAT');

	return (SharedStaticObjectTemplate*)previousTemplate;
}

SharedCellObjectTemplate* ObjectsToLua::parseCCLT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedCellObjectTemplate(iffStream);

	iffStream->openForm('CCLT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SHOT') {
			parseSHOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedCellObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('CCLT');

	return (SharedCellObjectTemplate*)previousTemplate;
}

SharedCreatureObjectTemplate* ObjectsToLua::parseSCOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedCreatureObjectTemplate(iffStream);

	iffStream->openForm('SCOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedCreatureObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SCOT');

	return (SharedCreatureObjectTemplate*)previousTemplate;
}

SharedResourceContainerObjectTemplate* ObjectsToLua::parseRCCT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedResourceContainerObjectTemplate(iffStream);

	iffStream->openForm('RCCT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedResourceContainerObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('RCCT');

	return (SharedResourceContainerObjectTemplate*)previousTemplate;
}

SharedShipObjectTemplate* ObjectsToLua::parseSSHP(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedShipObjectTemplate(iffStream);

	iffStream->openForm('SSHP');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedShipObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SSHP');

	return (SharedShipObjectTemplate*)previousTemplate;
}

SharedInstallationObjectTemplate* ObjectsToLua::parseSIOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedInstallationObjectTemplate(iffStream);

	iffStream->openForm('SIOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedInstallationObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SIOT');

	return (SharedInstallationObjectTemplate*)previousTemplate;
}

SharedFactoryObjectTemplate* ObjectsToLua::parseSFOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedFactoryObjectTemplate(iffStream);

	iffStream->openForm('SFOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedFactoryObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SFOT');

	return (SharedFactoryObjectTemplate*)previousTemplate;
}

SharedBuildingObjectTemplate* ObjectsToLua::parseSBOT(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedBuildingObjectTemplate(iffStream);

	iffStream->openForm('SBOT');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedBuildingObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SBOT');

	return (SharedBuildingObjectTemplate*)previousTemplate;
}

SharedBattlefieldMarkerObjectTemplate* ObjectsToLua::parseSBMK(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedBattlefieldMarkerObjectTemplate(iffStream);

	iffStream->openForm('SBMK');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedBattlefieldMarkerObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SBMK');

	return (SharedBattlefieldMarkerObjectTemplate*)previousTemplate;
}

SharedDraftSchematicObjectTemplate* ObjectsToLua::parseSDSC(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedDraftSchematicObjectTemplate(iffStream);

	iffStream->openForm('SDSC');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedDraftSchematicObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SDSC');

	return (SharedDraftSchematicObjectTemplate*)previousTemplate;
}

SharedManufactureSchematicObjectTemplate* ObjectsToLua::parseSMSC(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedManufactureSchematicObjectTemplate(iffStream);

	iffStream->openForm('SMSC');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedManufactureSchematicObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SMSC');

	return (SharedManufactureSchematicObjectTemplate*)previousTemplate;
}

SharedWaypointObjectTemplate* ObjectsToLua::parseSWAY(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedWaypointObjectTemplate(iffStream);

	iffStream->openForm('SWAY');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedWaypointObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SWAY');

	return (SharedWaypointObjectTemplate*)previousTemplate;
}

SharedPlayerObjectTemplate* ObjectsToLua::parseSPLY(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedPlayerObjectTemplate(iffStream);

	iffStream->openForm('SPLY');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedPlayerObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SPLY');

	return (SharedPlayerObjectTemplate*)previousTemplate;
}

SharedMissionObjectTemplate* ObjectsToLua::parseSMSO(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedMissionObjectTemplate(iffStream);

	iffStream->openForm('SMSO');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedMissionObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SMSO');

	return (SharedMissionObjectTemplate*)previousTemplate;
}

SharedConstructionContractObjectTemplate* ObjectsToLua::parseSCNC(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedConstructionContractObjectTemplate(iffStream);

	iffStream->openForm('SCNC');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedConstructionContractObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SCNC');

	return (SharedConstructionContractObjectTemplate*)previousTemplate;
}

SharedGuildObjectTemplate* ObjectsToLua::parseSGLD(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedGuildObjectTemplate(iffStream);

	iffStream->openForm('SGLD');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SUNI') {
			parseSUNI(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedGuildObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SGLD');

	return (SharedGuildObjectTemplate*)previousTemplate;
}

SharedGroupObjectTemplate* ObjectsToLua::parseSGRP(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedGroupObjectTemplate(iffStream);

	iffStream->openForm('SGRP');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SUNI') {
			parseSUNI(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedGroupObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SGRP');

	return (SharedGroupObjectTemplate*)previousTemplate;
}

SharedCountingObjectTemplate* ObjectsToLua::parseSCOU(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedCountingObjectTemplate(iffStream);

	iffStream->openForm('SCOU');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedCountingObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SCOU');

	return (SharedCountingObjectTemplate*)previousTemplate;
}

SharedJediManagerTemplate* ObjectsToLua::parseSJED(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedJediManagerTemplate(iffStream);

	iffStream->openForm('SJED');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SUNI') {
			parseSUNI(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedJediManagerTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SJED');

	return (SharedJediManagerTemplate*)previousTemplate;
}

SharedMissionDataObjectTemplate* ObjectsToLua::parseSMSD(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedMissionDataObjectTemplate(iffStream);

	iffStream->openForm('SMSD');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedMissionDataObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SMSD');

	return (SharedMissionDataObjectTemplate*)previousTemplate;
}

SharedMissionListEntryObjectTemplate* ObjectsToLua::parseSMLE(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedMissionListEntryObjectTemplate(iffStream);

	iffStream->openForm('SMLE');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedMissionListEntryObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('SMLE');

	return (SharedMissionListEntryObjectTemplate*)previousTemplate;
}

SharedTokenObjectTemplate* ObjectsToLua::parseSTOK(IffStream* iffStream, Template* previousTemplate) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedTokenObjectTemplate(iffStream);

	iffStream->openForm('STOK');

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'SITN') {
			parseSITN(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			//if (derv == '0009' || derv == '0007') {
			try {
				((SharedTokenObjectTemplate*)previousTemplate)->parseFileData(iffStream);
			} catch (Exception& e) {
				QString msg;
				msg += "exception caught parsing file data ->";
				msg += e.getMessage().c_str();
				msg += "of file:";
				msg += iffStream->getFileName().c_str();

				mainWindow->printToConsole(msg);
			}
			//}

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	iffStream->closeForm('STOK');

	return (SharedTokenObjectTemplate*)previousTemplate;
}

SharedObjectTemplate* ObjectsToLua::parseUnknownType(IffStream* iffStream, Template* previousTemplate, unsigned int type) {
	if (previousTemplate == NULL)
		previousTemplate = new SharedTangibleObjectTemplate(iffStream);

	iffStream->openForm(type);

	uint32 derv = iffStream->getNextFormType();

	if (derv == 'DERV') {
		loadDerv(iffStream, previousTemplate);

		derv = iffStream->getNextFormType();
	}

	while (derv != 0) {
		if (derv == 'STOT') {
			parseSTOT(iffStream, previousTemplate);
		} else {
			iffStream->openForm(derv);

			iffStream->closeForm(derv);
		}

		if (iffStream->getRemainingSubChunksNumber() > 0)
			derv = iffStream->getNextFormType();
		else
			derv = 0;
	}

	/*try {
		((SharedObjectTemplate*)previousTemplate)->parseFileData(iffStream);
	} catch (Exception& e) {
		QString msg;
		msg += "exception caught parsing file data ->";
		msg += e.getMessage().c_str();

		mainWindow->printToConsole(msg);
	}*/

	iffStream->closeForm(type);

	return (SharedObjectTemplate*)previousTemplate;
}

Template* ObjectsToLua::loadObjectVariables(IffStream* iffStream, Template* previousTemplate) {
	if (iffStream->getRemainingSubChunksNumber() == 0)
		return NULL;

	Template* templ = NULL;

	try {
		uint32 type = iffStream->getNextFormType();

		switch (type) {
		case 'SHOT':
			templ = parseSHOT(iffStream, previousTemplate);
			break;

		case 'STOT':
			templ = parseSTOT(iffStream, previousTemplate);
			break;

		case 'SWOT':
			templ = parseSWOT(iffStream, previousTemplate);
			break;

		case 'SUNI':
			templ = parseSUNI(iffStream, previousTemplate);
			break;

		case 'SITN':
			templ = parseSITN(iffStream, previousTemplate);
			break;

		case 'STAT':
			templ = parseSTAT(iffStream, previousTemplate);
			break;

		case 'CCLT':
			templ = parseCCLT(iffStream, previousTemplate);
			break;

		case 'SCOT':
			templ = parseSCOT(iffStream, previousTemplate);
			break;

		case 'SSHP':
			templ = parseSSHP(iffStream, previousTemplate);
			break;

		case 'RCCT':
			templ = parseRCCT(iffStream, previousTemplate);
			break;

		case 'SIOT':
			templ = parseSIOT(iffStream, previousTemplate);
			break;

		case 'SFOT':
			templ = parseSFOT(iffStream, previousTemplate);
			break;

		case 'SBOT':
			templ = parseSBOT(iffStream, previousTemplate);
			break;

		case 'SBMK':
			templ = parseSBMK(iffStream, previousTemplate);
			break;

		case 'SDSC':
			templ = parseSDSC(iffStream, previousTemplate);
			break;

		case 'SMSC':
			templ = parseSMSC(iffStream, previousTemplate);
			break;

		case 'SWAY':
			templ = parseSWAY(iffStream, previousTemplate);
			break;

		case 'SPLY':
			templ = parseSPLY(iffStream, previousTemplate);
			break;

		case 'SMSO':
			templ = parseSMSO(iffStream, previousTemplate);
			break;

		case 'SCNC':
			templ = parseSCNC(iffStream, previousTemplate);
			break;

		case 'SGLD':
			templ = parseSGLD(iffStream, previousTemplate);
			break;

		case 'SGRP':
			templ = parseSGRP(iffStream, previousTemplate);
			break;

		case 'SCOU':
			templ = parseSCOU(iffStream, previousTemplate);
			break;

		case 'SJED':
			templ = parseSJED(iffStream, previousTemplate);
			break;

		case 'SMSD':
			templ = parseSMSD(iffStream, previousTemplate);
			break;

		case 'SMLE':
			templ = parseSMLE(iffStream, previousTemplate);
			break;

		case 'STOK':
			templ = parseSTOK(iffStream, previousTemplate);
			break;
		default: {
			/*QTextStream in(&currentInheritance);
			uint32 reverseType = htonl(type);
			std::string tesT((char*)&reverseType, 4);
			QString var = tesT.c_str();

			if (currentInheritance.indexOf(var) == -1) {
				if (currentInheritance.size() != 0)
					in << "->";

				in << var;
			}*/

			//templ = parseUnknownType(iffStream, previousTemplate, type);
			uint32 reverseType = htonl(type);
			std::string tesT((char*)&reverseType, 4);
			QString var = tesT.c_str();
			QString msg;
			QTextStream stream(&msg);
			stream << "Unknown object template type : " << var << " in file : " << iffStream->getFileName().c_str();
			mainWindow->printToConsole(msg);
			break;
		}
		}
	} catch (Exception& e) {
		mainWindow->printToConsole("Error while parsing iff object template");
		QString msg;
		msg += "exception caught parsing file data ->";
		msg += e.getMessage().c_str();

		mainWindow->printToConsole(msg);

	} catch (...) {
		mainWindow->printToConsole("Error while parsing iff object template");
	}

	return templ;
}
