/*
 * SharedCountingObjectTemplate.h
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDCOUNTINGOBJECTTEMPLATE_H_
#define SHAREDCOUNTINGOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedCountingObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedCountingObjectTemplate(IffStream* str);
	~SharedCountingObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDCOUNTINGOBJECTTEMPLATE_H_ */
