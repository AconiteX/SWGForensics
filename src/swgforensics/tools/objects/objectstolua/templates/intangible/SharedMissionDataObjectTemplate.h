/*
 * SharedMissionDataObjectTemplate.h
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDMISSIONDATAOBJECTTEMPLATE_H_
#define SHAREDMISSIONDATAOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedMissionDataObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedMissionDataObjectTemplate(IffStream* str);
	~SharedMissionDataObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDMISSIONDATAOBJECTTEMPLATE_H_ */
