/*
 * CustomizationVariableMapping.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef CUSTOMIZATIONVARIABLEMAPPING_H_
#define CUSTOMIZATIONVARIABLEMAPPING_H_

#include <QMap>
#include <QString>

#include "PaletteColorCustomizationVariable.h"
#include "CustomizationVariableMap.h"

class CustomizationVariableMapping : public Param {
protected:
	//QMap<QString, PaletteColorCustomizationVariable*> variables;
	QVector<CustomizationVariableMap> variables;


public:
	CustomizationVariableMapping() : Param() {
	}

	~CustomizationVariableMapping() {
		/*QMap<QString, PaletteColorCustomizationVariable*>::const_iterator i;

		for (i = variables.constBegin(); i != variables.constEnd(); ++i)
			delete i.value();*/

		//std::cout << "DELETING CustomizationVariableMapping\n";
	}

	QString toString();

	void toString(QString& str) {
		//std::cout << "entering void toString(QString& str)\n";
		//str = test;
	}

	bool parse(Chunk* source);

	void parseType1(IffStream* source);
};


#endif /* CUSTOMIZATIONVARIABLEMAPPING_H_ */
