/*
 * SharedInstallationObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDINSTALLATIONOBJECTTEMPLATE_H_
#define SHAREDINSTALLATIONOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedInstallationObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedInstallationObjectTemplate(IffStream* str);
	~SharedInstallationObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};



#endif /* SHAREDINSTALLATIONOBJECTTEMPLATE_H_ */
