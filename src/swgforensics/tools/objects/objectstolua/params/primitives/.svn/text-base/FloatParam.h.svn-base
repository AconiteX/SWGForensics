/*
 * FloatParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef FLOATPARAM_H_
#define FLOATPARAM_H_

#include "../TemplateBase.h"

class FloatParam : public TemplateBase<float> {
	float min;
	float max;
public:
	FloatParam() : TemplateBase<float>(0.f) {
		setType(FLOAT);
		min = 0;
		max = 0;
	}

	FloatParam& operator= (float val) {
		create(val);

		return *this;
	}

	QString toString() {
		QString str;

		if (min != 0 || max != 0) {
			QTextStream in(&str);
			in << "{" << min << ", " << max << "}";
		} else {
			QTextStream in(&str);
			in << get();
		}

		return str;
	}

	virtual bool parse(Chunk* source) {
		uint8 readCase = source->getUnsignedByte();
		uint8 byte2 = source->getUnsignedByte();

		if (readCase == 1 && byte2 == 0x20) {
			create(source->getFloat());

			return true;
		} else if (readCase == 2 && byte2 == 0x20) {
			IffStream* iffStream = source->getIffStream();

			QString text;
			QTextStream stream(&text);

			stream << "unhandled FloatParam type! in ";
			stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);
		} else if (readCase == 3 && byte2 == 0x20) {
			/*IffStream* iffStream = source->getIffStream();

			QString text;
			QTextStream stream(&text);

			stream << "READ CASE 3 MOTHER FUCKER FloatParam type! in ";
			stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);*/

			min = source->getFloat();
			max = source->getFloat();
		}

			/* else {
			create(0.f);
		}*/

		return false;
	}
};


#endif /* FLOATPARAM_H_ */
