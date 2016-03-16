/*
 * SlotDescriptorFilename.h
 *
 *  Created on: 11/07/2009
 *      Author: TheAnswer
 */

#ifndef SLOTDESCRIPTORFILENAME_H_
#define SLOTDESCRIPTORFILENAME_H_

#include "primitives/StringParam.h"

#include "../slot/SlotDescriptor.h"
#include "../objectstolua.h"

class SlotDescriptorFilename : public StringParam {

public:
	/*QString toString() {
		QVector<QString> descriptors;

		QString file = get();

		if (file != "") {
			QString trePath = SWGTRESDIRECTORY;

			QString fullPath = trePath + file;

			SlotDescriptor parser(fullPath);

			descriptors = parser.getSlotDescriptors();
		}

		QString var;
		QTextStream stream(&var);

		stream << "{";

		for (int i = 0; i < descriptors.size(); ++i) {
			StringParam param(descriptors[i]);
			stream << param.toString();

			if (i + 1 < descriptors.size())
				stream << ", ";
		}

		stream << "}";

		return var;
	}*/

};


#endif /* SLOTDESCRIPTORFILENAME_H_ */
