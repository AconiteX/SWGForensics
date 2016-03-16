/*
 * Exception.h
 *
 *  Created on: 03-feb-2009
 *      Author: TheAnswer
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "../../lang.h"

#include <iostream>


class Exception {
protected:
	std::string message;

	//StackTrace trace;

public:
	Exception();
	Exception(const std::string& msg);

	virtual ~Exception();

	void printStackTrace();

	// setters and getters
	inline void setMessage(const std::string msg) {
		message = msg;
	}

	inline std::string getMessage() {
		return message;
	}

};

#endif /* EXCEPTION_H_ */
