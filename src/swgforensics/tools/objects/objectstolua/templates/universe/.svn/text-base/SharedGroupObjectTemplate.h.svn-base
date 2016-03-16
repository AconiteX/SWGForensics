/*
 * SharedGroupObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDGROUPOBJECTTEMPLATE_H_
#define SHAREDGROUPOBJECTTEMPLATE_H_

#include "../SharedUniverseObjectTemplate.h"

class SharedGroupObjectTemplate : public SharedUniverseObjectTemplate {

public:
	SharedGroupObjectTemplate(IffStream* str);
	~SharedGroupObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDGROUPOBJECTTEMPLATE_H_ */
