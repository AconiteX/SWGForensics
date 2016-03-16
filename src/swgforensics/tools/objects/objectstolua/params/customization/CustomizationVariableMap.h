/*
 * CustomizationVariableMap.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef CUSTOMIZATIONVARIABLEMAP_H_
#define CUSTOMIZATIONVARIABLEMAP_H_

typedef unsigned int uint32;
typedef unsigned char uint8;

#include "../Param.h"
#include "../primitives/StringParam.h"
#include "../primitives/IntegerParam.h"

class CustomizationVariableMap : public Param {
	StringParam sourceVariable;
	StringParam dependentVariable;

public:
	CustomizationVariableMap() : Param() {
		setType(CUSTOMIZATIONVARIABLEMAP);
	}

	~CustomizationVariableMap() {
	}

	QString toString() {
		QString var;
		QTextStream stream(&var);

		stream << "{";

		stream << sourceVariable.toString() << ", " << dependentVariable.toString();

		stream << "}";

		/*
		stream << "sourceVariable" << " = " << sourceVariable.toString() << "\n";
		stream << "dependentVariable" << " = " << dependentVariable.toString() << "\n";
		*/

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

			//std::cout << "parsing CVMM:[" << varName.toStdString() << "]\n";

			if (varName == "sourceVariable") {
				sourceVariable.parse(var);
			} else if (varName == "dependentVariable") {
				dependentVariable.parse(var);
			}

			iffStream->closeChunk('XXXX');
		}

		return true;
	}
};


#endif /* CUSTOMIZATIONVARIABLEMAP_H_ */
