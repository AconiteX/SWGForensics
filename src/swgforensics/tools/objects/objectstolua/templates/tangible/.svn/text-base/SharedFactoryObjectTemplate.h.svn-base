/*
 * SharedFactoryObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDFACTORYOBJECTTEMPLATE_H_
#define SHAREDFACTORYOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedFactoryObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedFactoryObjectTemplate(IffStream* str);
	~SharedFactoryObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDFACTORYOBJECTTEMPLATE_H_ */
