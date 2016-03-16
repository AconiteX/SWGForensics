/*
 * Exception.cpp
 *
 *  Created on: 03-feb-2009
 *      Author: TheAnswer
 */

#include "Exception.h"

Exception::Exception() {
}

Exception::Exception(const std::string& msg) {
	message = msg;
}

Exception::~Exception() {
}

void Exception::printStackTrace() {
	/*System::out << message << "\n";
	trace.print();*/
}
