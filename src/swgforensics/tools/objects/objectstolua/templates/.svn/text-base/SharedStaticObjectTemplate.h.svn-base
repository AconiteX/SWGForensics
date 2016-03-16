/*
 * SharedStaticObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDSTATICOBJECTTEMPLATE_H_
#define SHAREDSTATICOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"
#include "tangible/SharedBuildingObjectTemplate.h"

#include "../params.h"

class SharedStaticObjectTemplate : public SharedBuildingObjectTemplate {
protected:


public:
	SharedStaticObjectTemplate(IffStream* str);
	~SharedStaticObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDSTATICOBJECTTEMPLATE_H_ */
