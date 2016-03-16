/*
 * SharedResourceContainerObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_
#define SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedResourceContainerObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedResourceContainerObjectTemplate(IffStream* str);
	~SharedResourceContainerObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDRESOURCECONTAINEROBJECTTEMPLATE_H_ */
