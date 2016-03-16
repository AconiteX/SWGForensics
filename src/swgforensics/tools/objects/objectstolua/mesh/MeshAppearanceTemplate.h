/*
 * MeshAppearanceTemplate.h
 *
 *  Created on: 06/12/2010
 *      Author: TheAnswer
 */

#ifndef MESHAPPEARANCETEMPLATE_H_
#define MESHAPPEARANCETEMPLATE_H_

#include <QString>

#include "../../../../../system/iff/chunk/Chunk.h"

#include "../../../../swgforensics.h"

#include "../floormesh/FloorMesh.h"

#include "../objectstolua.h"

#include <QFile>


class MeshVertex {
public:
    float x, y, z;

    MeshVertex() {

    }
};

class MeshTriangle {
public:
    int vertex1, vertex2, vertex3;

    MeshTriangle() {

    }
};

class MeshData {
public:
    QVector<float> vertexData;
    QVector<int> triangleIndexes;

    QVector<MeshVertex> vertexes;
    QVector<MeshTriangle> triangles;

    MeshData() {

    }

};

class MeshAppearanceTemplate {
public:
	IffStream* iffStream;

        QVector<MeshData> meshes;

public:
	MeshAppearanceTemplate(const QString& file) {
           // SWGForensics::instance->printToConsole("trying to parse file " + file);

		try {
			iffStream = new IffStream(file.toStdString());
		} catch (...) {
			iffStream = NULL;

			SWGForensics::instance->printToConsole("unable to open file " + file);

			return;
		}

		parse();

                SWGForensics::instance->printToConsole("parsed file " + file);

                /*QFile* qFile = new QFile(file);

                QString fileName = qFile->fileName();

                QString name = fileName.remove("D:/swg tres/");

                QString newName = "D:/filesforserver/" + name;

                if (!qFile->copy(newName)) {
                	SWGForensics::instance->printToConsole("unable to copy file " + newName);
                }

                delete qFile;*/
	}

	~MeshAppearanceTemplate() {
		delete iffStream;
	}

	void parse() {
		iffStream->openForm('MESH');

                uint32 version = iffStream->getNextFormType();
                iffStream->openForm(version);


		iffStream->openForm('APPR');
		//ignoring this atm
		iffStream->closeForm('APPR');


                parseSPS();


                iffStream->closeForm(version);
		iffStream->closeForm('MESH');
	}

	void parseSPS(){
		iffStream->openForm('SPS ');
		iffStream->openForm('0001');

		int count = 0;

		iffStream->openChunk('CNT ');

		count = iffStream->getInt();

		iffStream->closeChunk();

                for (int i = 1; i <= count; ++i) {
                        parseVertexData(i);
                }

		iffStream->closeForm('0001');
		iffStream->closeForm('SPS ');
	}

	void parseVertexData(int idx) {
            int formVersion = 0;'0000';// + idx;

            QString idxText;
            QTextStream idxStream(&idxText);

            idxStream << idx;

            int lengthOfText = idxText.length();

            for (int i = 0; i < 4 - lengthOfText; ++i)
                idxText = "0" + idxText;

            std::string mda = idxText.toStdString();

            for (int i = 0; i < 4; ++i) {
                char a = mda[i];

                formVersion = formVersion << 8;
                formVersion += (int)a;
            }

            QString test;
            QTextStream testSt(&test);
            testSt << hex << formVersion;

            //SWGForensics::instance->printToConsole(test + " " + idxText);


		iffStream->openForm(formVersion);

		iffStream->openChunk('NAME');

		QString shaderName;
		iffStream->getString(shaderName);

		iffStream->closeChunk();

		iffStream->openChunk('INFO');
		iffStream->closeChunk();

		iffStream->openForm('0001');


		iffStream->openChunk('INFO');
		iffStream->closeChunk();

		iffStream->openForm('VTXA');

		iffStream->openForm('0003');

		iffStream->openChunk('INFO');

                iffStream->getInt();

                int numVertices = iffStream->getInt();

		iffStream->closeChunk();

                Chunk* vertexDataChunk = iffStream->openChunk('DATA');

                int vertexDataChunkSize = vertexDataChunk->getChunkSize();

                int intBytesPerVertex = vertexDataChunkSize / numVertices;

                QString text;
                QTextStream stream(&text);

                stream << "butes per vertex " << intBytesPerVertex << " num vertives " << numVertices;

                //SWGForensics::instance->printToConsole(text);

                MeshData meshData;

                //vertexData.append(iffStream->getFloat());

                for (int i = 0; i < numVertices; ++i) {
                    float x = iffStream->getFloat();
                    float y = iffStream->getFloat();
                    float z = iffStream->getFloat();

                    MeshVertex vert;
                    vert.x = x;
                    vert.y = y;
                    vert.z = z;

                    meshData.vertexes.append(vert);

                    vertexDataChunk->shiftOffset(intBytesPerVertex - 12);
                }

                //vertexDataChunk->shiftOffset(intBytesPerVertex);

               // SWGForensics::instance->printToConsole("parsed vertexes");

		iffStream->closeChunk('DATA');
		iffStream->closeForm('0003');

                iffStream->closeForm('VTXA');

		Chunk* indexData = iffStream->openChunk('INDX');

		int indexCount = iffStream->getInt();

		for (int i = 1; i <= indexCount; ++i) {
                    meshData.triangleIndexes.append(indexData->getUnsignedShort());
		}

                int triangleCount = indexCount / 3;

                for (int i = 0; i < triangleCount; ++i) {
                    int a = meshData.triangleIndexes.at(i);
                    int b = meshData.triangleIndexes.at(i + 1);
                    int c = meshData.triangleIndexes.at(i + 2);

                    MeshTriangle triangle;
                    triangle.vertex1 = a;
                    triangle.vertex2 = b;
                    triangle.vertex3 = c;

                    meshData.triangles.append(triangle);
                }

                meshes.append(meshData);

		iffStream->closeChunk();


		iffStream->closeForm('0001');

		iffStream->closeForm(formVersion);
	}

};



#endif /* MESHAPPEARANCETEMPLATE_H_ */
