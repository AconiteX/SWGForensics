/*
 * PaletteColorCustomizationVariables.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef PALETTECOLORCUSTOMIZATIONVARIABLES_H_
#define PALETTECOLORCUSTOMIZATIONVARIABLES_H_

#include <QMap>
#include <QString>

#include "PaletteColorCustomizationVariable.h"

class PaletteColorCustomizationVariables : public Param {
protected:
	//QMap<QString, PaletteColorCustomizationVariable*> variables;
	QVector<PaletteColorCustomizationVariable> variables;


public:
	PaletteColorCustomizationVariables() : Param() {
	}

	~PaletteColorCustomizationVariables() {
		/*QMap<QString, PaletteColorCustomizationVariable*>::const_iterator i;

		for (i = variables.constBegin(); i != variables.constEnd(); ++i)
			delete i.value();*/

		//std::cout << "DELETING PaletteColorCustomizationVariables\n";
	}

	QString toString();

	void toString(QString& str) {
		//std::cout << "entering void toString(QString& str)\n";
		//str = test;
	}

	bool parse(Chunk* source);

	void parseType1(IffStream* source);
};


#endif /* PALETTECOLORCUSTOMIZATIONVARIABLES_H_ */
