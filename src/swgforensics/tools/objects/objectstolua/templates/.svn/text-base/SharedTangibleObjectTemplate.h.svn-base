/*
 * SharedTangibleObjectTemplate.h
 *
 *  Created on: 21-feb-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDTANGIBLEOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"

#include "../params.h"

class SharedTangibleObjectTemplate : public SharedObjectTemplate {
protected:
	PaletteColorCustomizationVariables paletteColorCustomizationVariables;
	RangedIntCustomizationVariables rangedIntCustomizationVariables;

	SocketDestinations socketDestinations;

	StringParam structureFootprintFileName;

	BoolParam useStructureFootprintOutline;
	BoolParam targetable;

	CertificationsRequired certificationsRequired;
	CustomizationVariableMapping customizationVariableMapping;

public:
	SharedTangibleObjectTemplate(IffStream* str);
	~SharedTangibleObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDTANGIBLEOBJECTTEMPLATE_H_ */
