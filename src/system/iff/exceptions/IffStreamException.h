#ifndef IFFSTREAMEXCEPTION_H_
#define IFFSTREAMEXCEPTION_H_

#include "../../lang.h"

#include "../IffStream.h"


#include "Exception.h"

#include <sstream>

//#include <QtConcurrent>

class IffStreamException : public Exception {
protected:
	IffStream* iffStream;

public:
	IffStreamException(IffStream* stream) : Exception("IffStreamException\n") {
		iffStream = stream;
	}

	IffStream* getIffStream() {
		return iffStream;
	}

};

#endif /*IFFSTREAMEXCEPTION_H_*/
