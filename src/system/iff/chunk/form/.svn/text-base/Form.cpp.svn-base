#include "Form.h"

Form::Form(Chunk* parent, uint32 type, uint32 size, char* data) : Chunk(parent, FORM, size, data) {
	formType = type;
	
	/*char* fType = new char[4];
	*(uint32*)fType = htonl(type);
	string sfType(fType, 4);
	cout << "Creating FORM:[" << sfType << "]\n";
	delete [] fType;*/
}

Form::~Form() {
}
