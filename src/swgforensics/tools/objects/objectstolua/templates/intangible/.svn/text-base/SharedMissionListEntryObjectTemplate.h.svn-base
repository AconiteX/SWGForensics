/*
 * SharedMissionListEntryObjectTemplate.h
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDMISSIONLISTENTRYOBJECTTEMPLATE_H_
#define SHAREDMISSIONLISTENTRYOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedMissionListEntryObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedMissionListEntryObjectTemplate(IffStream* str);
	~SharedMissionListEntryObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDMISSIONLISTENTRYOBJECTTEMPLATE_H_ */
