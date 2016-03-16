/*
 * SharedIntangibleObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDINTANGIBLEOBJECTTEMPLATE_H_
#define SHAREDINTANGIBLEOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"

#include "../params.h"

class SharedIntangibleObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedIntangibleObjectTemplate(IffStream* str);
	~SharedIntangibleObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDINTANGIBLEOBJECTTEMPLATE_H_ */
