/*
 * RangedIntCustomizationVariables.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLES_H_
#define RANGEDINTCUSTOMIZATIONVARIABLES_H_

#include <QMap>
#include <QString>

#include "RangedIntCustomizationVariable.h"

class RangedIntCustomizationVariables : public Param {
protected:
	//QMap<QString, PaletteColorCustomizationVariable*> variables;
	QVector<RangedIntCustomizationVariable> variables;


public:
	RangedIntCustomizationVariables() : Param() {
	}

	~RangedIntCustomizationVariables() {
		/*QMap<QString, PaletteColorCustomizationVariable*>::const_iterator i;

		for (i = variables.constBegin(); i != variables.constEnd(); ++i)
			delete i.value();*/

		//std::cout << "DELETING RangedIntCustomizationVariables\n";
	}

	QString toString();

	void toString(QString& str) {
		//std::cout << "entering void toString(QString& str)\n";
		//str = test;
	}

	bool parse(Chunk* source);

	void parseType1(IffStream* source);
};


#endif /* RANGEDINTCUSTOMIZATIONVARIABLES_H_ */
