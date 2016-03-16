/*
 * SharedCellObjectTemplate.h
 *
 *  Created on: 17-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDCELLOBJECTTEMPLATE_H_
#define SHAREDCELLOBJECTTEMPLATE_H_

#include "SharedObjectTemplate.h"

#include "../params.h"

class SharedCellObjectTemplate : public SharedObjectTemplate {
protected:


public:
	SharedCellObjectTemplate(IffStream* str);
	~SharedCellObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDCELLOBJECTTEMPLATE_H_ */
