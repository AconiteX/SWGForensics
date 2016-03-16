/*
 * SharedUniverseObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDUNIVERSEOBJECTTEMPLATE_H_
#define SHAREDUNIVERSEOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"

#include "../params.h"

class SharedUniverseObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedUniverseObjectTemplate(IffStream* str);
	~SharedUniverseObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};



#endif /* SHAREDUNIVERSEOBJECTTEMPLATE_H_ */
