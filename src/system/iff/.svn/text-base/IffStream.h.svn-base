#ifndef IFFSTREAM_H_
#define IFFSTREAM_H_

#include "../lang.h"

//#include "chunk/Chunk.h"

//#include "chunk/form/Form.h"

#include <QVector>

#include <iostream>
#include <fstream>

class Chunk;

//#include "chunk/Chunk.h"

class IffStream {
	std::ifstream fileStream;
	char* dataBuffer;
	uint32 dataSize;

	std::string fileName;

	QVector<Chunk*> mainChunks;
	int lastOpenedChunk;

	Chunk* openedChunk;

private:
	void loadChunks(Chunk* chunk);

public:
	IffStream(const std::string& filename);
	~IffStream();

	bool load();

	Chunk* openForm(uint32 formType);
	bool closeForm(uint32 formType);

	int getDataSize();

	int getSubChunksNumber();
	int getRemainingSubChunksNumber();

	Chunk* openChunk(uint32 chunk = 0);
	void closeChunk(uint32 chunk = 0);

	void skipChunks(int num = 1);

	inline std::string& getFileName() {
		return fileName;
	}

	uint32 getFormType();
	uint32 getNextFormType();

	// io operations
	void getString(std::string& str);
	void getString(QString& str);

	float getFloat();
	int getInt();
	uint32 getUnsignedInt();

	uint8 getByte();
	uint64 getUnsignedLong();
	int64 getLong();

	void getBytes(int bytes, void* dest);

	void close();
};

#endif /*IFFSTREAM_H_*/
