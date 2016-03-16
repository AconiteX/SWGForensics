/*
 * SharedPlayerObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDPLAYEROBJECTTEMPLATE_H_
#define SHAREDPLAYEROBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedPlayerObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedPlayerObjectTemplate(IffStream* str);
	~SharedPlayerObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDPLAYEROBJECTTEMPLATE_H_ */
