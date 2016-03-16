#ifndef INVALIDFILETYPEEXCEPTION_H_
#define INVALIDFILETYPEEXCEPTION_H_

#include "IffStreamException.h"

#include <sstream>

class InvalidFileTypeException : public IffStreamException {
public:
	InvalidFileTypeException(IffStream* iffstream) : IffStreamException(iffstream) {
		std::stringstream sstr;
		sstr << "InvalidFileTypeException on file:[" << iffstream->getFileName() << "]\n";
		message = sstr.str();
	}
};

#endif /*INVALIDFILETYPEEXCEPTION_H_*/
