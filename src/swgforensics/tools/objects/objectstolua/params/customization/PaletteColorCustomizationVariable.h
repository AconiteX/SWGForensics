/*
 * PaletteColorCustomizationVariable.h
 *
 *  Created on: 23-feb-2009
 *      Author: TheAnswer
 */

#ifndef PALETTECOLORCUSTOMIZATIONVARIABLE_H_
#define PALETTECOLORCUSTOMIZATIONVARIABLE_H_

typedef unsigned int uint32;
typedef unsigned char uint8;

#include "../Param.h"
#include "../primitives/StringParam.h"
#include "../primitives/IntegerParam.h"

class PaletteColorCustomizationVariable : public Param {
	StringParam variableName;
	StringParam palettePathName;
	IntegerParam defaultPaletteIndex;

public:
	PaletteColorCustomizationVariable() : Param() {
		setType(PALETTECOLORCUSTOMIZATION);

	}

	~PaletteColorCustomizationVariable() {

	}

	QString toString() {
		QString var;
		QTextStream stream(&var);
		/*stream << "variableName" << " = " << variableName.toString() << "\n";
		stream << "palettePathName" << " = " << palettePathName.toString() << "\n";
		stream << "defaultPaletteIndex" << " = " << defaultPaletteIndex.toString() << "\n";*/

		stream << "{";

		stream << variableName.toString() << ", " << palettePathName.toString()
				<< ", " << defaultPaletteIndex.toString();

		stream << "}";

		return var;
	}

	bool parse(Chunk* source) {
		IffStream* iffStream = source->getIffStream();

		Chunk* chunk = iffStream->openChunk('PCNT');

		if (chunk == NULL) {
			std::cout << "could not open pcnt\n";
			return false;
		}

		int vars = iffStream->getInt();

		iffStream->closeChunk('PCNT');

		for (int j = 0; j < vars; ++j) {
			Chunk* var = iffStream->openChunk('XXXX');

			QString varName;
			var->getString(varName);

			//std::cout << "parsing pccv:[" << varName.toStdString() << "]\n";

			if (varName == "variableName") {
				variableName.parse(var);
			} else if (varName == "palettePathName") {
				palettePathName.parse(var);
			} else if (varName == "defaultPaletteIndex") {
				defaultPaletteIndex.parse(var);
			}

			iffStream->closeChunk('XXXX');
		}

		return true;
	}

	QString getVariableName() {
		return variableName.get();
	}

};


#endif /* PALETTECOLORCUSTOMIZATIONVARIABLE_H_ */
