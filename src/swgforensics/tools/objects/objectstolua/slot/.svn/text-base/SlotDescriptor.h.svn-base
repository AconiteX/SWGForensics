/*
 * SlotDescriptor.h
 *
 *  Created on: 11/07/2009
 *      Author: TheAnswer
 */

#ifndef SLOTDESCRIPTOR_H_
#define SLOTDESCRIPTOR_H_

#include <QString>

#include "../../../../../system/iff/chunk/Chunk.h"

#include "../../../../swgforensics.h"

class SlotDescriptor {
	QString arrangement;

	IffStream* iffStream;

	QVector<QString> slotDescriptors;

public:
	SlotDescriptor(const QString& file) {
		try {
			iffStream = new IffStream(file.toStdString());
		} catch (...) {
			iffStream = NULL;

			SWGForensics::instance->printToConsole("unable to open file " + file);

			return;
		}

		parse();
	}

	~SlotDescriptor() {
		delete iffStream;
	}

	void parse() {
		try {
			iffStream->openForm('SLTD');

			iffStream->openForm('0000');

			Chunk* data = iffStream->openChunk('DATA');

			try {
				QString descriptor;

				while (true) {
					data->getString(descriptor);

					slotDescriptors.append(descriptor);
				}
			} catch (...) {

			}

			iffStream->closeChunk();

			iffStream->closeForm('0000');

			iffStream->closeForm('ARGD');
		} catch (...) {
			QString err = "unable to parse file ";
			err += iffStream->getFileName().c_str();
			SWGForensics::instance->printToConsole(err);
		}
	}

	inline QVector<QString>& getSlotDescriptors() {
		return slotDescriptors;
	}
};

#endif /* SLOTDESCRIPTOR_H_ */
