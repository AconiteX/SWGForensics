/*
 * SharedWeaponObjectTemplate.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef SHAREDWEAPONOBJECTTEMPLATE_H_
#define SHAREDWEAPONOBJECTTEMPLATE_H_

#include "../SharedTangibleObjectTemplate.h"

class SharedWeaponObjectTemplate : public SharedTangibleObjectTemplate {
	StringParam weaponEffect;
	IntegerParam weaponEffectIndex;
	IntegerParam attackType;

public:
	SharedWeaponObjectTemplate(IffStream* str);
	~SharedWeaponObjectTemplate();

	void parseFileData(IffStream* str);

	void parseVariableData(const QString& varName, Chunk* data);

	void toLua(QTextStream& buffer);
};


#endif /* SHAREDWEAPONOBJECTTEMPLATE_H_ */
