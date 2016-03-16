/*
 * SharedDraftSchematicObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_
#define SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedDraftSchematicObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedDraftSchematicObjectTemplate(IffStream* str);
	~SharedDraftSchematicObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDDRAFTSCHEMATICOBJECTTEMPLATE_H_ */
