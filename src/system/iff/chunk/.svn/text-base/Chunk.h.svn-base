#ifndef CHUNK2_H_
#define CHUNK2_H_

#include "../../lang.h"
#include <QVector>
#include <QObject>

#include "../exceptions.h"

#include <QObject>
#include <QString>

class Chunk;
class IffStream;

class Chunk {
protected:
	IffStream* iffStream;
	Chunk* parent;

	uint32 chunkID;
	uint32 chunkSize;
	char* chunkData;

	QVector<Chunk*> subChunks;
	int lastOpenedSubChunk;

	int offset;

public:
	const static uint32 FORM = 'FORM';
	const static uint32 DATA = 'DATA';
	const static uint32 LIST = 'LIST';
	const static uint32 CAT = 'CAT ';

public:
	Chunk(uint32 id, uint32 size, char* data);
	Chunk(Chunk* par, uint32 id, uint32 size, char* data);
	virtual ~Chunk();

	virtual void process();

	inline void setIffStream(IffStream* iff) {
		iffStream = iff;
	}

	inline IffStream* getIffStream() {
		return iffStream;
	}

	inline void setLastOpenedSubChunk(int value) {
		lastOpenedSubChunk = value;
	}

	inline void getChildren(QVector<Chunk*>& child) {
		child = subChunks;
	}

	inline bool isFORM() {
		return chunkID == FORM;
	}

	inline bool isDATA() {
		return chunkID == DATA;
	}

	inline Chunk* getParent() {
		return parent;
	}

	void addChunk(Chunk* chunk) {
		subChunks.append(chunk);
	}

	Chunk* getChunk(int idx) {
		if (idx >= subChunks.size())
			throw ArrayIndexOutOfBoundsException(idx);
		else
			return subChunks.at(idx);
	}

	Chunk* getNextChunk() {
		if (lastOpenedSubChunk + 1 >= subChunks.size())
			throw ArrayIndexOutOfBoundsException(lastOpenedSubChunk + 1);
		else
			return subChunks.at(++lastOpenedSubChunk);
	}

	uint32 getChunksSize() {
		return subChunks.size();
	}

	inline int getLastOpenedChunkIdx() {
		return lastOpenedSubChunk;
	}

	inline uint32 getChunkID() {
		return chunkID;
	}

	inline int getChunkSize() {
		return chunkSize;
	}

	inline char* getChunkData() {
		return chunkData;
	}

	inline void shiftOffset(int num) {
                if ((offset += num) > chunkSize)
			throw ArrayIndexOutOfBoundsException();
	}

	inline uint32 getUnsignedInt() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		uint32 result = *(uint32*)(chunkData + offset);
		offset += 4;

		return result;
	}

	inline int getSignedInt() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		int result = *(int*)(chunkData + offset);
		offset += 4;

		return result;
	}

	inline uint8 getUnsignedByte() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		uint8 result = *(uint8*)(chunkData + offset);
		offset++;

		return result;
	}

	inline int8 getSignedByte() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		int8 result = *(int8*)(chunkData + offset);
		offset++;

		return result;
	}

	inline uint16 getUnsignedShort() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		uint16 result = *(uint16*)(chunkData + offset);
		offset += 2;

		return result;
	}

	inline int16 getSignedShort() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		int16 result = *(int16*)(chunkData + offset);
		offset += 2;

		return result;
	}

	inline void getString(std::string& str) {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		str.clear();

		uint8 result = *(uint8*)(chunkData + offset);

		if (result != 0) {
			str.append(chunkData + offset);
		}

		offset += (str.size() + 1);
	}

	inline void getString(QString& str) {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		str.clear();

		uint8 result = *(uint8*)(chunkData + offset);

		if (result != 0) {
			str.append(chunkData + offset);
		}

		offset += (str.size() + 1);
	}

	inline uint64 getUnsignedLong() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		uint64 result = *(uint64*)(chunkData + offset);
		offset += 8;

		return result;
	}

	inline int64 getSignedLong() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		int64 result = *(int64*)(chunkData + offset);
		offset += 8;

		return result;
	}

	inline float getFloat() {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		float result = *(float*)(chunkData + offset);
		offset += 4;

		return result;
	}

	inline void getBytes(int bytes, void* dest) {
		if (offset >= chunkSize)
			throw ArrayIndexOutOfBoundsException();

		memcpy(dest, (chunkData + offset), bytes);

		offset += bytes;
	}

};

#endif /*CHUNK_H_*/
