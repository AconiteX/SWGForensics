/*
 * StringParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef STRINGPARAM_H_
#define STRINGPARAM_H_

#include "../TemplateBase.h"

class StringParam : public TemplateBase<QString> {
public:
	StringParam() : TemplateBase<QString>("") {
		setType(STRING);
	}

	StringParam(const QString& val) : TemplateBase<QString>(val) {
		setType(STRING);
	}

	virtual QString toString() {
		//return get();
		QString ret;
		QTextStream stream(&ret);

		stream << "\"" << get() << "\"";

		return ret;
	}

	virtual bool parse(Chunk* source) {
		int readCase = source->getUnsignedByte();

		if (readCase == 1) {
			QString val;
			source->getString(val);

			//std::cout << "read case 1:[" << val.toStdString() << "]\n";
			create(val);

			return true;
		}/* else if (readCase == 0) {
			create("");
			std::cout << "read case 0\n";
		} else {
			throw Exception("Unknown case in StringParam::parse(Chunk* dat)");
		}*/

		return false;
	}

	StringParam& operator= (const QString& val) {
		create(val);

		return *this;
	}

	QString& operator-= (const QString& val) {
		return value;
	}
};

#endif /* STRINGPARAM_H_ */
