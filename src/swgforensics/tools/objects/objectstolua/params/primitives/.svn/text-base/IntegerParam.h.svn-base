/*
 * IntegerParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef INTEGERPARAM_H_
#define INTEGERPARAM_H_

#include "../TemplateBase.h"

#include "../../../../../swgforensics.h"

class IntegerParam : public TemplateBase<int> {

public:
	IntegerParam() : TemplateBase<int>(0) {
		setType(INTEGER);
	}

	IntegerParam& operator= (int val) {
		create(val);

		return *this;
	}

	QString toString() {
		QString str;
		QTextStream in(&str);

		in << get();

		return str;
	}

	virtual bool parse(Chunk* source) {
		uint8 readCase = source->getUnsignedByte();
		uint8 byte2 = source->getUnsignedByte();

		if (readCase == 1 && byte2 == 0x20) {
			create(source->getUnsignedInt());

			return true;
		} else if (readCase == 2 && byte2 == 0x20) {
			/*int size = source->getUnsignedInt();

			QVector<IntegerParam> params;

			for (int i = 0; i < size; ++i) {
				int unknown = source->getUnsignedInt();

				IntegerParam param;

				if (param.parse(source))
					params.push_back(param);
			}*/

			IffStream* iffStream = source->getIffStream();

			QString text;
			QTextStream stream(&text);

			stream << "unhandled IntegerParam type! in ";
			stream << iffStream->getFileName().c_str() << "\n";
			SWGForensics::instance->printToConsole(text);


		}/* else {
			create(0);
		}*/

		return false;
	}

};


#endif /* INTEGERPARAM_H_ */
