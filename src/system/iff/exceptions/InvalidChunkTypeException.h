#ifndef INVALIDCHUNKTYPEEXCEPTION_H_
#define INVALIDCHUNKTYPEEXCEPTION_H_

#include "IffStreamException.h"

#include <sstream>

class InvalidChunkTypeException : public IffStreamException {
public:
	InvalidChunkTypeException(IffStream* iffstream) : IffStreamException(iffstream) {
		std::stringstream sstr;
		sstr << "InvalidChunkTypeException on file:[" << iffstream->getFileName() << "]\n";
		message = sstr.str();
	}
};

#endif /*INVALIDCHUNKTYPEEXCEPTION_H_*/
