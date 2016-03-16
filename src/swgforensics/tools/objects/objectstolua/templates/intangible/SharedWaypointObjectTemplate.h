/*
 * SharedWaypointObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDWAYPOINTOBJECTTEMPLATE_H_
#define SHAREDWAYPOINTOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedWaypointObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedWaypointObjectTemplate(IffStream* str);
	~SharedWaypointObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDWAYPOINTOBJECTTEMPLATE_H_ */
