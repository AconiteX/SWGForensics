/*
 * BoolParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef BOOLPARAM_H_
#define BOOLPARAM_H_

#include "../TemplateBase.h"

class BoolParam : public TemplateBase<bool> {
public:
	BoolParam() : TemplateBase<bool>(false) {
		setType(BOOL);
	}

	BoolParam& operator= (bool val) {
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

		if (readCase == 1) {
			create(source->getUnsignedByte());

			return true;
		}

		return false;
		/*else {
			create(false);
		}*/
	}
};


#endif /* BOOLPARAM_H_ */
