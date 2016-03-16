/*
 * SharedShipObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDSHIPOBJECTTEMPLATE_H_
#define SHAREDSHIPOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedShipObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedShipObjectTemplate(IffStream* str);
	~SharedShipObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDSHIPOBJECTTEMPLATE_H_ */
