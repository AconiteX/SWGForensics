/*
 * CustomizationVariableMapping.cpp
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#include "CustomizationVariableMapping.h"
#include "../../../../../swgforensics.h"

bool CustomizationVariableMapping::parse(Chunk* source) {
	//variables.clear();
	//std::cout << "parsing CustomizationVariableMapping\n";

	uint8 unk = source->getUnsignedByte();
	uint32 num = source->getUnsignedInt();

	if (num == 0) {
		//std::cout << "0 PCCVs\n";
		return false;
	} else {
		//std::cout << num << " CVMMs\n";
		//return;
	}

	variables.clear();

	IffStream* iffStream = source->getIffStream();

	if (iffStream == NULL) {
		std::cout << "iffstream null\n";
		return false;
	}

	for (int i = 0; i < num; ++i) {
		//try {
		uint8 unk2 = iffStream->getByte();

		switch (unk2) {
		case 0:
			continue;
		case 1:
			parseType1(iffStream);
			continue;
		case 2: {
			QString text;
			QTextStream stream(&text);

			stream << "unhandled CustomizationVariableMapping type! in ";
			stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);
			// throw unhandled type!
			continue;
		}
		}
		/*} catch (...) {
			continue;
		}*/
	}

	return true;
}

void CustomizationVariableMapping::parseType1(IffStream* iffStream) {
	uint32 type = iffStream->getUnsignedInt();

	iffStream->closeChunk();

	Chunk* chunk = iffStream->openForm('CVMM');

	if (chunk == NULL) {
		std::cout << "could not open CVMM\n";
		return;
	}

	CustomizationVariableMap cvmm;
	cvmm.parse(chunk);

	//QString name = cvmm.getVariableName();

	/*if (!name.isEmpty() && !variables.contains(name))
		variables[name] = pccv;*/
	variables.append(cvmm);

	iffStream->closeForm('CVMM');

	iffStream->openChunk('XXXX');

}

QString CustomizationVariableMapping::toString() {
	QString var;
	QTextStream stream(&var);

	stream << "{";

	for (int i = 0; i < variables.size(); ++i) {
		stream << variables[i].toString();

		if (i + 1 < variables.size())
			stream << ", \n\t\t\t";
	}
	/*for (int i = 0; i < variables.size(); ++i) {
		stream << i + 1 << ":\n" << variables[i].toString() << "\n";
	}*/

	stream << "}";

	return var;
}
