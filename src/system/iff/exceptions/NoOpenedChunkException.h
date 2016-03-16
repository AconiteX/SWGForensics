#ifndef NOOPENEDCHUNKEXCEPTION_H_
#define NOOPENEDCHUNKEXCEPTION_H_

#include "IffStreamException.h"

#include <sstream>

class NoOpenedChunkException : public IffStreamException {

public:
	NoOpenedChunkException(IffStream* iffstream) : IffStreamException(iffstream) {
		std::stringstream sstr;
		sstr << "NoOpenedChunkException on file:[" << iffstream->getFileName() << "]\n";
		message = sstr.str();
	}
};

#endif /*NOOPENEDCHUNKEXCEPTION_H_*/
