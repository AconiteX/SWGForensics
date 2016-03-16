/*
 * SharedGuildObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDGUILDOBJECTTEMPLATE_H_
#define SHAREDGUILDOBJECTTEMPLATE_H_

#include "../SharedUniverseObjectTemplate.h"

class SharedGuildObjectTemplate : public SharedUniverseObjectTemplate {

public:
	SharedGuildObjectTemplate(IffStream* str);
	~SharedGuildObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDGUILDOBJECTTEMPLATE_H_ */
