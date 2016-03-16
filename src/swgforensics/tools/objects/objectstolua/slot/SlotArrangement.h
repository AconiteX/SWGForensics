/*
 * SlotArrangement.h
 *
 *  Created on: 11/07/2009
 *      Author: TheAnswer
 */

#ifndef SLOTARRANGEMENT_H_
#define SLOTARRANGEMENT_H_

#include <QString>

#include "../../../../../system/iff/chunk/Chunk.h"

class SlotArrangement {
	QVector<QString> arrangements;

	IffStream* iffStream;

public:
	SlotArrangement(const QString& file) {
		try {
			iffStream = new IffStream(file.toStdString());
		} catch (...) {
			iffStream = NULL;

			SWGForensics::instance->printToConsole("unable to open file " + file);

			return;
		}

		parse();
	}

	~SlotArrangement() {
		delete iffStream;
	}

	void parse() {
		try {
			iffStream->openForm('ARGD');

			iffStream->openForm('0000');

			Chunk* data = iffStream->openChunk('ARG ');

			try {
				QString descriptor;

				while (true) {
					data->getString(descriptor);

					arrangements.append(descriptor);
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

	inline QVector<QString>& getArrangements() {
		return arrangements;
	}

};


#endif /* SLOTARRANGEMENT_H_ */
