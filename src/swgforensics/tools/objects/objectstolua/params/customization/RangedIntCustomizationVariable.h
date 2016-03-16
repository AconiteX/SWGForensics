/*
 * RangedIntCustomizationVariable.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef RANGEDINTCUSTOMIZATIONVARIABLE_H_
#define RANGEDINTCUSTOMIZATIONVARIABLE_H_

typedef unsigned int uint32;
typedef unsigned char uint8;

#include "../Param.h"
#include "../primitives/StringParam.h"
#include "../primitives/IntegerParam.h"


class RangedIntCustomizationVariable : public Param {
	StringParam variableName;
	IntegerParam minValueInclusive;
	IntegerParam defaultValue;
	IntegerParam maxValueExclusive;

public:
	RangedIntCustomizationVariable() : Param() {
		setType(RANGEDINTCUSTOMIZATIONVARIABLE);
	}

	~RangedIntCustomizationVariable() {
	}

	QString toString() {
		QString var;
		QTextStream stream(&var);
		/*stream << "variableName" << " = " << variableName.toString() << "\n";
		stream << "minValueInclusive" << " = " << minValueInclusive.toString() << "\n";
		stream << "defaultValue" << " = " << defaultValue.toString() << "\n";
		stream << "maxValueExclusive" << " = " << maxValueExclusive.toString() << "\n";*/

		stream << "{";

		stream << variableName.toString() << ", "
				<< minValueInclusive.toString() << ", "
				<< defaultValue.toString() << ", "
				<< maxValueExclusive.toString();

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

			//std::cout << "parsing RICV:[" << varName.toStdString() << "]\n";

			if (varName == "variableName") {
				variableName.parse(var);
			} else if (varName == "minValueInclusive") {
				minValueInclusive.parse(var);
			} else if (varName == "defaultValue") {
				defaultValue.parse(var);
			} else if (varName == "maxValueExclusive") {
				maxValueExclusive.parse(var);
			}

			iffStream->closeChunk('XXXX');
		}

		return true;
	}

	QString getVariableName() {
		return variableName.get();
	}

};


#endif /* RANGEDINTCUSTOMIZATIONVARIABLE_H_ */
