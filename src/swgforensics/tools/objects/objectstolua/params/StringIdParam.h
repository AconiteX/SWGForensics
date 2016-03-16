/*
 * StringIdParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef STRINGIDPARAM_H_
#define STRINGIDPARAM_H_

#include "TemplateBase.h"

#include <QString>

#include "primitives/StringParam.h"

class StringIdParamData {
	StringParam file;
	StringParam stringId;
public:
	StringIdParamData(const QString& File, const QString& id) {
		file = File;
		stringId = id;
	}

	StringIdParamData(const StringParam& File, const StringParam& id) {
		file = File;
		stringId = id;
	}

	StringIdParamData() {
		file = "";
		stringId = "";
	}


	bool operator< (const StringIdParamData& val) const {
		return false;
	}

	bool operator> (const StringIdParamData& val) const {
		return false;
	}

	StringIdParamData& operator+= (const StringIdParamData& val) {
		return *this;
	}

	StringIdParamData& operator-= (const StringIdParamData& val) {
		return *this;
	}


	friend class StringIdParam;
};

class StringIdParam : public TemplateBase<StringIdParamData> {

public:
	StringIdParam() : TemplateBase<StringIdParamData>(StringIdParamData("", "")) {
		setType(STRINGID);
	}

	~StringIdParam() {
	}

	QString toString() {
		return getFullString();
	}

	virtual bool parse(Chunk* source) {
		int readCase = source->getUnsignedByte();

		if (readCase != 1) {
			//create(StringIdParamData());
			return false;
		}

		StringParam stfFile;
		stfFile.parse(source);

		StringParam stringId;
		stringId.parse(source);

		create(StringIdParamData(stfFile, stringId));

		return true;
	}

	StringIdParam& operator= (const StringIdParamData& custom) {
		create(custom);

		return *this;
	}

	QString getFullString() {
		QString file = get().file.get();
		//std::cout << "testFile:[" << file.toStdString() << "]\n";

		QString stringId = get().stringId.get();
		//std::cout << "testStringId:[" << stringId.toStdString() << "]\n";

		if (stringId.isEmpty())
			return get().file.toString();
		else return "\"@" + file + ":" + stringId + "\"";
	}

};


#endif /* STRINGIDPARAM_H_ */
