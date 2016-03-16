/*
 * SharedBattlefieldMarkerObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_
#define SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedBattlefieldMarkerObjectTemplate : public SharedTangibleObjectTemplate {

public:
	SharedBattlefieldMarkerObjectTemplate(IffStream* str);
	~SharedBattlefieldMarkerObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDBATTLEFIELDMARKEROBJECTTEMPLATE_H_ */
