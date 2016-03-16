/*
 * SharedJediManagerTemplate.h
 *
 *  Created on: 22-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDJEDIMANAGERTEMPLATE_H_
#define SHAREDJEDIMANAGERTEMPLATE_H_

#include "../SharedUniverseObjectTemplate.h"

class SharedJediManagerTemplate : public SharedUniverseObjectTemplate {

public:
	SharedJediManagerTemplate(IffStream* str);
	~SharedJediManagerTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDJEDIMANAGERTEMPLATE_H_ */
