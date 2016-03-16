#ifndef FORM_H_
#define FORM_H_

#include "../../../lang.h"

#include "../Chunk.h"

class Form : public Chunk {
protected:
	uint32 formType;

public:
	Form(Chunk* parent, uint32 type, uint32 size, char* data);
	~Form();

	inline uint32 getFormType() {
		return formType;
	}

};

#endif /*FORM_H_*/
