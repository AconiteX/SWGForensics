/*
 * PortalLayoutFilename.h
 *
 *  Created on: 30/01/2010
 *      Author: TheAnswer
 */

#ifndef PORTALLAYOUTFILENAME_H_
#define PORTALLAYOUTFILENAME_H_

#include "primitives/StringParam.h"

#include "../objectstolua.h"

#include "PortalLayout.h"

class PortalLayoutFilename : public StringParam {

public:
	QString toString() {
		QString ret;
		QTextStream stream(&ret);

		stream << "\"" << get() << "\"";

		return ret;
	}

	int getTotalCellNumber() {
		int totalCellNumber = 0;

		QString file = get();

		if (file != "") {
			QString trePath = SWGTRESDIRECTORY;

			QString fullPath = trePath + file;

			PortalLayout parser(fullPath);

			totalCellNumber = parser.getCellNumber();

			/*QString err;
			QTextStream stream(&err);
			stream << "parsed file " << file << " with total cell number " << totalCellNumber;
			SWGForensics::instance->printToConsole(err);*/
		}

		return totalCellNumber;
	}

};


#endif /* PORTALLAYOUTFILENAME_H_ */
