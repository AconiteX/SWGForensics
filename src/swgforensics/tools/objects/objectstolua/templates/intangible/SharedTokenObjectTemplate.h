/*
 * SharedTokenObjectTemplate.h
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDTOKENOBJECTTEMPLATE_H_
#define SHAREDTOKENOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedTokenObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedTokenObjectTemplate(IffStream* str);
	~SharedTokenObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDTOKENOBJECTTEMPLATE_H_ */
