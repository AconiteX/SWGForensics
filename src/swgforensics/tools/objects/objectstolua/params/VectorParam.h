/*
 * VectorParam.h
 *
 *  Created on: 22-feb-2009
 *      Author: TheAnswer
 */

#ifndef VECTORPARAM_H_
#define VECTORPARAM_H_

#include "TemplateBase.h"

/*
template <class Type>
class VectorParamData {
public:
	VectorParamData() {

	}
};

template <class Data>
class VectorParam : public TemplateBase<VectorParamData<Type> > {
	int size;
	QVector<Data> data;
public:
	VectorParam() : TemplateBase<VectorParamData<Type>, VectorParamData<Type> >(VectorParamData<Type>()) {

	}
};*/

template <class Data>
class VectorParam : public Param {
	QVector<Data> vectorData;

public:
	VectorParam() : Param() {
	}

	~VectorParam() {
	}

	QString toString() {
		QString var;
		QTextStream stream(&var);

		stream << "{";
		for (int i = 0; i < vectorData.size(); ++i) {
			stream << vectorData[i].toString();

			if (i + 1 < vectorData.size())
				stream << ",";
		}

		stream << "}";

		return var;
	}

	bool parse(Chunk* data) {
		int size = data->getUnsignedInt();

		/*uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();*/

		QVector<Data> newData;

		for (int i = 0; i < size; ++i) {
			Data param;

			if (param.parse(data))
				newData.push_back(param);
		}

		if (!newData.isEmpty()) {
			vectorData = newData;
			return true;
		} else {
			return false;
		}
	}
};



#endif /* VECTORPARAM_H_ */
