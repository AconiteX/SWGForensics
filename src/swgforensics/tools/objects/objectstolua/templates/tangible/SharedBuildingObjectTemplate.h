/*
 * SharedBuildingObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDBUILDINGOBJECTTEMPLATE_H_
#define SHAREDBUILDINGOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedBuildingObjectTemplate : public SharedTangibleObjectTemplate {
	StringParam terrainModificationFileName;
	StringParam interiorLayoutFileName;

public:
	SharedBuildingObjectTemplate(IffStream* str);
	~SharedBuildingObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDBUILDINGOBJECTTEMPLATE_H_ */
