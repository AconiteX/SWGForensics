/*
 * SharedObjectTemplate.h
 *
 *  Created on: 19-feb-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDOBJECTTEMPLATE_H_
#define SHAREDOBJECTTEMPLATE_H_

#include "Template.h"
#include <QMap>

#include "../params.h"
#include "../LuaWriter.h"

#include "../params/ArrangementDescriptorFilename.h"
#include "../params/SlotDescriptorFilename.h"
#include "../params/PortalLayoutFilename.h"


#include "ui_objectstolua.h"

class SharedObjectTemplate : public Template {
protected:
	QMap<QString, Param*> variables;

	StringIdParam objectName;
	StringIdParam detailedDescription;
	StringIdParam lookAtText;

	BoolParam snapToTerrain;
	IntegerParam containerType;
	IntegerParam containerVolumeLimit;

	StringParam tintPallete;
	SlotDescriptorFilename slotDescriptorFilename;
	ArrangementDescriptorFilename arrangementDescriptorFilename;
	StringParam appearanceFilename;
	PortalLayoutFilename portalLayoutFilename;
	IntegerParam totalCellNumber;
	StringParam clientDataFile;

	IntegerParam collisionMaterialFlags;
	IntegerParam collisionMaterialPassFlags;
	FloatParam scale;
	IntegerParam collisionMaterialBlockFlags;
	IntegerParam collisionActionFlags;
	IntegerParam collisionActionPassFlags;
	IntegerParam collisionActionBlockFlags;
	IntegerParam gameObjectType;
	IntegerParam clientGameObjectType;
	BoolParam sendToClient;
	FloatParam scaleThresholdBeforeExtentTest;
	FloatParam clearFloraRadius;
	IntegerParam surfaceType;
	FloatParam noBuildRadius;
	BoolParam onlyVisibleInTools;
	FloatParam locationReservationRadius;

public:
	SharedObjectTemplate(IffStream* str);
	~SharedObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void printVariables(Ui::ObjectsToLuaClass* ui);
	void printVariable(const QString& varName, Ui::ObjectsToLuaClass* ui);

	void toLua(QTextStream& buffer);
	void variablesToLua(QTextStream& buffer);

	Param* getVariable(const QString& name) {
		if (!variables.contains(name))
			return NULL;
		else
			return variables[name];
	}

	QString getObjectName() {
		return objectName.getFullString();
	}

	QString getDetailedDescription() {
		return detailedDescription.getFullString();
	}

	QString getLookAtText() {
		return lookAtText.getFullString();
	}

};


#endif /* SHAREDOBJECTTEMPLATE_H_ */
