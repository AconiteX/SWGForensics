/*
 * SharedMissionObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDMISSIONOBJECTTEMPLATE_H_
#define SHAREDMISSIONOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedMissionObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedMissionObjectTemplate(IffStream* str);
	~SharedMissionObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDMISSIONOBJECTTEMPLATE_H_ */
