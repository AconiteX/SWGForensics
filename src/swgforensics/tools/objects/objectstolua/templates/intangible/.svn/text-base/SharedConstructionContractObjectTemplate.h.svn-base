/*
 * SharedConstructionContractObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_
#define SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_

#include "../SharedIntangibleObjectTemplate.h"

class SharedConstructionContractObjectTemplate : public SharedIntangibleObjectTemplate {

public:
	SharedConstructionContractObjectTemplate(IffStream* str);
	~SharedConstructionContractObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};

#endif /* SHAREDCONSTRUCTIONCONTRACTOBJECTTEMPLATE_H_ */
