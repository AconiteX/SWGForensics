#ifndef NOCHUNKSEXCEPTION_H_
#define NOCHUNKSEXCEPTION_H_

#include "IffStreamException.h"

#include <sstream>

class NoChunksException : public IffStreamException {
public:
	NoChunksException(IffStream* iffstream) : IffStreamException(iffstream) {
		std::stringstream sstr;
		sstr << "NoChunksException on file:[" << iffstream->getFileName() << "]\n";
		message = sstr.str();
	}
};

#endif /*NOCHUNKSEXCEPTION_H_*/
