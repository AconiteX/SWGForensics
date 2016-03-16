/*
 * SharedManufactureSchematicObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDMANUFACTURESCHEMATICOBJECTTEMPLATE_H_
#define SHAREDMANUFACTURESCHEMATICOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedManufactureSchematicObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedManufactureSchematicObjectTemplate(IffStream* str);
	~SharedManufactureSchematicObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDMANUFACTURESCHEMATICOBJECTTEMPLATE_H_ */
