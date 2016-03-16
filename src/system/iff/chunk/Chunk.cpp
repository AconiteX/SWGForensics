#include "Chunk.h"

#include "../chunks.h"

Chunk::Chunk(uint32 id, uint32 size, char* data) {
	parent = NULL;

	chunkID = id;
	chunkSize = size;
	chunkData = data;

	offset = 0;

	lastOpenedSubChunk = -1;

	iffStream = NULL;

	/*char* fType = new char[4];
	*(uint32*)fType = htonl(id);
	string sfType(fType, 4);
	cout << "Creating CHUNK with ID:[" << sfType << "] and size: [" << hex << chunkSize << "]\n";
	delete [] fType;*/
}

Chunk::Chunk(Chunk* par, uint32 id, uint32 size, char* data) {
	parent = par;

	chunkID = id;
	chunkSize = size;
	chunkData = data;

	offset = 0;

	lastOpenedSubChunk = -1;

	iffStream = NULL;

	/*char* fType = new char[4];
	*(uint32*)fType = htonl(id);
	string sfType(fType, 4);
	cout << "Creating CHUNK with ID:[" << sfType << "] and size: [" << hex << chunkSize << "]\n";
	delete [] fType;*/
}

Chunk::~Chunk() {
	for (int i = 0; i < subChunks.size(); i++) {
		delete subChunks.at(i);
	}
}

void Chunk::process() {
}
