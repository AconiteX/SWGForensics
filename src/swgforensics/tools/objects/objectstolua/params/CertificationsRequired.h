/*
 * CertificationsRequired.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef CERTIFICATIONSREQUIRED_H_
#define CERTIFICATIONSREQUIRED_H_

#include <QVector>

#include "primitives/StringParam.h"

class CertificationsRequired : public Param {
	QVector<StringParam> certifications;

public:
	CertificationsRequired() : Param() {
	}

	~CertificationsRequired() {
	}

	QString toString() {
		QString var;
		QTextStream stream(&var);

		stream << "{";
		for (int i = 0; i < certifications.size(); ++i) {
			stream << certifications[i].toString();

			if (i + 1 < certifications.size())
				stream << ",";
		}

		stream << "}";

		return var;
	}

	bool parse(Chunk* data) {
		//certifications.clear();

		uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();

		QVector<StringParam> certs;

		for (int i = 0; i < num; ++i) {
			StringParam certification;

			if (certification.parse(data))
				certs.push_back(certification);
		}

		if (!certs.isEmpty()) {
			certifications = certs;

			return true;
		}

		return false;
	}
};


#endif /* CERTIFICATIONSREQUIRED_H_ */
