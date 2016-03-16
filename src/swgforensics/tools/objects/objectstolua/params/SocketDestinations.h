/*
 * SocketDestinations.h
 *
 *  Created on: 16-abr-2009
 *      Author: TheAnswer
 */

#ifndef SOCKETDESTINATIONS_H_
#define SOCKETDESTINATIONS_H_

#include <QVector>

#include "primitives/IntegerParam.h"

class SocketDestinations : public Param {
	QVector<IntegerParam> destinations;

public:
	SocketDestinations() : Param() {
	}

	~SocketDestinations() {
	}

	QString toString() {
		QString var;
		QTextStream stream(&var);

		stream << "{";
		for (int i = 0; i < destinations.size(); ++i) {
			stream << destinations[i].toString();

			if (i + 1 < destinations.size())
				stream << ",";
		}

		stream << "}";

		return var;
	}

	bool parse(Chunk* data) {
		//destinations.clear();
		uint8 unk = data->getUnsignedByte();
		uint32 num = data->getUnsignedInt();

		QVector<IntegerParam> sockets;

		for (int i = 0; i < num; ++i) {
			IntegerParam destination;

			if (destination.parse(data))
				sockets.push_back(destination);

			//destinations.push_back(destination);
		}

		if (!sockets.isEmpty()) {
			destinations = sockets;

			return true;
		}

		return false;
	}
};


#endif /* SOCKETDESTINATIONS_H_ */
