#include "IffStream.h"

#include "chunk/Chunk.h"

#include "chunk/form/Form.h"
#include "chunk/data/Data.h"

#include "chunks.h"
#include "exceptions.h"

#include <winsock2.h>

using namespace std;

IffStream::IffStream(const std::string& filename) {
	fileName = filename;

	//cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>";
	//cout << "<file>" << filename << "</file>\n";

	fileStream.open(filename.c_str(), fstream::in | fstream::out | fstream::binary);

	if (!fileStream.is_open()) {
		throw InvalidFileTypeException(this);
		cout << "Error loading file\n";
		return;
	}

	dataBuffer = NULL;
	openedChunk = NULL;

	lastOpenedChunk = -1;

	load();
}

IffStream::~IffStream() {
	close();

	if (fileStream.is_open())
		fileStream.close();

	if (dataBuffer != NULL)
		delete [] dataBuffer;

	for (int i = 0; i < mainChunks.size(); i++) {
		delete mainChunks.at(i);
	}
}

bool IffStream::load() {
	fileStream.seekg(0, ios::end);
	dataSize = fileStream.tellg();
	fileStream.seekg(0, ios::beg);

	if (dataSize < 8) {
		fileStream.close();
		throw InvalidFileTypeException(this);
	}

	// allocate memory:
	dataBuffer = new char[dataSize];

	// read data as a block:
	fileStream.read(dataBuffer, dataSize);
	fileStream.close();

	loadChunks(NULL);

	return true;
}

void IffStream::loadChunks(Chunk* chunk) {
	char* data;
	uint32 totalSize;

	if (chunk == NULL)
		data = dataBuffer;
	else
		data = chunk->getChunkData();

	uint32 offset = 0;

	if (chunk == NULL)
		totalSize = dataSize;
	else
		totalSize = chunk->getChunkSize();

	while (offset < (totalSize - 4)) {
		Chunk* newChunk = NULL;

		uint32 type = htonl(*(uint32*)(data + offset));
		offset += 4;

		uint32 size = htonl(*(uint32*)(data + offset));
		offset += 4;

		switch (type) {
		case ('FORM'): {
			uint32 formType = htonl(*(uint32*)(data + offset));

			Form* newForm = new Form(chunk, formType, size, data + offset + 4);
			loadChunks(newForm);

			newChunk = newForm;
			break;
		}
		case ('DATA'): {
			Data* newData = new Data(chunk, data + offset, size);

			newChunk = newData;
			break;
		}
		default: {
			/*string chunkType(data + (offset - 8), 4);
			cout << "Unknown Chunk Type:[" << chunkType << "]\n";*/
			newChunk = new Chunk(chunk, type, size, data + offset);
			break;
		}
		}

		if (chunk == NULL)
			mainChunks.append(newChunk);
		else
			chunk->addChunk(newChunk);

		newChunk->setIffStream(this);

		offset += size;
	}

	//cout << "Finished processing chunkSize [" << totalSize << "] i: [" << offset << "]\n";
}

Chunk* IffStream::openForm(uint32 formType) {
	Chunk* chunkObject = NULL;

	if (openedChunk == NULL)
		chunkObject = mainChunks.at(++lastOpenedChunk);
	else
		chunkObject = openedChunk->getNextChunk();

	if (!chunkObject->isFORM()) {
		cout << "Could not open chunk:[" << formType << "]!\n";
		Chunk* test = NULL;
		test->getChunkSize();
		return NULL;
	}

	Form* formObject = (Form*)chunkObject;

	if (formObject->getFormType() != formType) {
		cout << "Could not open chunk[" << formType << "]!\n";
		Chunk* test = NULL;
		test->getChunkSize();
		return NULL;
	}

	openedChunk = formObject;

	/*char* fType = new char[4];
	*(uint32*)fType = htonl(formType);
	string sfType(fType, 4);
	cout << "<FORM>\n<type>" << sfType << "</type>\n";
	delete [] fType;*/


	//cout << "Opened FORM:[" << hex << formType << "]\n";

	return openedChunk;
}

int IffStream::getSubChunksNumber() {
	if (openedChunk == NULL)
		return mainChunks.size();
	else
		return openedChunk->getChunksSize();
}

int IffStream::getRemainingSubChunksNumber() {
	if (openedChunk == NULL) {
		return mainChunks.size() - (lastOpenedChunk + 1);
	} else {
		int result = openedChunk->getChunksSize() - (openedChunk->getLastOpenedChunkIdx() + 1);
		return result;
	}
}

int IffStream::getDataSize() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getChunkSize();
}

uint32 IffStream::getFormType() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	if (!openedChunk->isFORM())
		throw InvalidChunkTypeException(this);

	Form* form = (Form*)openedChunk;

	uint32 type = form->getFormType();

	//cout << "Type:[" << hex << type << "]\n";

	return type;
}

uint32 IffStream::getNextFormType() {
	Chunk* child;

	if (openedChunk == NULL)
		child = mainChunks.at((lastOpenedChunk + 1));
	else {
		int nextChunk = openedChunk->getLastOpenedChunkIdx();
		child = openedChunk->getChunk(++nextChunk);
	}

	if (!child->isFORM())
		throw InvalidChunkTypeException(this);

	Form* form = (Form*) child;

	return form->getFormType();
}

bool IffStream::closeForm(uint32 formType) {
	closeChunk(formType);

	return true;
}

Chunk* IffStream::openChunk(uint32 chunk) {
	Chunk* chunkObject = NULL;

	if (openedChunk == NULL)
		chunkObject = mainChunks.at(++lastOpenedChunk);
	else
		chunkObject = openedChunk->getNextChunk();

	if (chunk != 0 && chunkObject->getChunkID() != chunk) {
		Chunk* test = NULL;
		test->getChunkSize();
		cout << "Could not open chunk:[" << chunk << "] expecting [" << chunkObject->getChunkID() << "]!\n";
		return NULL;
	}

	openedChunk = chunkObject;

	/*char* fType = new char[4];
	*(uint32*)fType = htonl(chunk);
	string sfType(fType, 4);
	cout << "<" << sfType << ">\n";
	delete [] fType;*/

	//cout << "Opened CHUNK:[" << hex << chunk << "]\n";

	return openedChunk;
}

void IffStream::closeChunk(uint32 chunk) {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	/*char* fType = new char[4];
	*(uint32*)fType = htonl(openedChunk->getChunkID());
	string sfType(fType, 4);
	cout << "</" << sfType << ">\n";
	delete [] fType;*/

	openedChunk = openedChunk->getParent();

}

void IffStream::close() {

}

void IffStream::skipChunks(int num) {
	if (openedChunk != NULL) {
		int chunks = openedChunk->getLastOpenedChunkIdx();
		chunks += num;
		openedChunk->setLastOpenedSubChunk(chunks);
	} else
		lastOpenedChunk += num;
}

void IffStream::getString(string& str) {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	openedChunk->getString(str);
}

void IffStream::getString(QString& str) {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	openedChunk->getString(str);
}

float IffStream::getFloat() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getFloat();
}

int IffStream::getInt() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getSignedInt();
}

uint32 IffStream::getUnsignedInt() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getUnsignedInt();
}

uint8 IffStream::getByte() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getUnsignedByte();
}

uint64 IffStream::getUnsignedLong() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getUnsignedLong();
}

int64 IffStream::getLong() {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	return openedChunk->getSignedLong();
}

void IffStream::getBytes(int bytes, void* dest) {
	if (openedChunk == NULL)
		throw NoOpenedChunkException(this);

	openedChunk->getBytes(bytes, dest);
}
