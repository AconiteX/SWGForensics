/*
 * ArrayIndexOutOfBoundsException.h
 *
 *  Created on: 03-feb-2009
 *      Author: TheAnswer
 */

#ifndef ARRAYINDEXOUTOFBOUNDSEXCEPTION_H_
#define ARRAYINDEXOUTOFBOUNDSEXCEPTION_H_

#include "Exception.h"

#include <sstream>

class ArrayIndexOutOfBoundsException : public Exception {
public:
	ArrayIndexOutOfBoundsException() : Exception("ArrayIndexOutOfBoundsException\n") {
	}

	ArrayIndexOutOfBoundsException(int index) :	Exception() {
		std::stringstream str;
		str << "ArrayIndexOutOfBoundsException at " << index << "\n";
		message = str.str();
	}
};


#endif /* ARRAYINDEXOUTOFBOUNDSEXCEPTION_H_ */
