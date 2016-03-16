/*
 * FloorMesh.h
 *
 *  Created on: 02/12/2010
 *      Author: TheAnswer
 */

#ifndef FLOORMESH_H_
#define FLOORMESH_H_

#include <QString>
#include <QFile>
#include <QTextStream>

#include "../../../../../system/iff/chunk/Chunk.h"
#include "../../../../../system/util/Vector.h"
#include "../../../../../system/util/Vector3.h"
#include "../../../../../system/util/Triangle.h"


#include <cmath>

#include "../../../floor/AABBTree.h"

class Vert {
public:
	float x, y, z;

	Vert() {

	}

	Vert(float px, float py, float pz) {
		x = px;
		y = py;
		z = pz;
	}

	Vector3 getPos() const {
		return Vector3(x, y, z);
	}

};

class Nods {
public:
	float x1, y1, z1, x2, y2, z2;
	int var1, var2, var3, var4;

	Nods() {

	}

};

class Bedg {
public:
	int var1, var2;
	char var3;

	Bedg() {

	}

	void printToConsole() const {
		QString err;
		QTextStream stream(&err);

		/*stream << "x1:" << vert->x1 << " y1:" << vert->y1 << " z1:" << vert->z1 << endl;
					stream << "x2:" << vert->x2 << " y2:" << vert->y2 << " z2:" << vert->z2 << endl;
					stream << "var1: " << vert->var1 << " var2:" << vert->var2 << " var3:" << vert->var3 << " var4" << vert->var4;*/

		stream << "var1:" << var1 << " var2:" << var2 << " var3:" << bool(var3);

		SWGForensics::instance->printToConsole(err);
	}
};

class PathNode {
public:
	int var1, var2, var3, var4;
	float var5, var6, var7, var8;

	PathNode() {

	}

	void printToConsole() const {
		QString err;
		QTextStream stream(&err);

		/*stream << "x1:" << vert->x1 << " y1:" << vert->y1 << " z1:" << vert->z1 << endl;
						stream << "x2:" << vert->x2 << " y2:" << vert->y2 << " z2:" << vert->z2 << endl;
						stream << "var1: " << vert->var1 << " var2:" << vert->var2 << " var3:" << vert->var3 << " var4" << vert->var4;*/

		stream << "var1:" << var1 << " var2:" << var2 << " var3:" << var3 << " var4:" << var4 << endl;
		stream << "var5:" << var5 << " var6:" << var6 << " var7:" << var7 << " var8:" << var8;

		SWGForensics::instance->printToConsole(err);
	}
};

class PathEdge {
public:
	int var1, var2, var3, var4;

	PathEdge() {

	}

	void printToConsole() const {
		QString err;
		QTextStream stream(&err);

		/*stream << "x1:" << vert->x1 << " y1:" << vert->y1 << " z1:" << vert->z1 << endl;
						stream << "x2:" << vert->x2 << " y2:" << vert->y2 << " z2:" << vert->z2 << endl;
						stream << "var1: " << vert->var1 << " var2:" << vert->var2 << " var3:" << vert->var3 << " var4" << vert->var4;*/

		stream << "var1:" << var1 << " var2:" << var2 << " var3:" << var3 << " var4:" << var4;

		SWGForensics::instance->printToConsole(err);
	}
};

class Tri : public Triangle {
public:
	Vector<Tri*> neighbors;

	int var1, var2, var3, id, left, right, down;
	float var8, var9, var10;
	byte var11, var12, var13, var14;
	int var15, var16, var17, var18;

	bool visited;

	Tri() {
		visited = false;
	}

	uint32 getID() {
		return id;
	}

	inline Vector3 getBarycenter() {
		float x = (vertices[0][0] + vertices[1][0] + vertices[2][0]) / 3.f;
		float y = (vertices[0][1] + vertices[1][1] + vertices[2][1]) / 3.f;
		float z = (vertices[0][2] + vertices[1][2] + vertices[2][2]) / 3.f;

		return Vector3(x, y, z);
	}

	Vector<Tri*>* getNeighbors() {
		return &neighbors;
	}

	void setVisited() {
		visited = true;
	}

	bool isVisited() {
		return visited;
	}

	void printToConsole() const {
		QString err;
		QTextStream stream(&err);

		/*stream << "x1:" << vert->x1 << " y1:" << vert->y1 << " z1:" << vert->z1 << endl;
							stream << "x2:" << vert->x2 << " y2:" << vert->y2 << " z2:" << vert->z2 << endl;
							stream << "var1: " << vert->var1 << " var2:" << vert->var2 << " var3:" << vert->var3 << " var4" << vert->var4;*/

		stream << var1 << " " << var2 << " " << var3 << " " << id << " " << left << " " << right << " " << down << endl;
		stream << var8 << " " << var9 << " " << var10 << endl;
		stream << var11 << " " << var12 << " " << var13 << " " << var14 << endl;
		stream << var15 << " " << var16 << " " << var17 << " " << var18 << endl;

		SWGForensics::instance->printToConsole(err);
	}
};

class FloorMesh {
public:
	IffStream* iffStream;

	QVector<Vert> vertices;
	QVector<Tri*> tris;
	QVector<Nods> nodes;
	QVector<AABBNode*> aabbNodes;
	QVector<Bedg> edges;
	QVector<PathNode> pathNodes;
	QVector<PathEdge> pathEdges;
	QVector<int> ecnt;
	QVector<int> estr;

	float calculateManhattanDistance(Tri* node1, Tri* node2) {
		Vector3 bary = node1->getBarycenter();
		Vector3 bary2 = node1->getBarycenter();

		return bary2.squaredDistanceTo(bary2);

		//return abs(bary.getX() - bary2.getX()) + abs(bary.getY() - bary2.getY()) + abs(bary.getZ() - bary2.getZ());
	}


	FloorMesh(const QString& file) {
		try {
			iffStream = new IffStream(file.toStdString());
		} catch (Exception& e) {
			iffStream = NULL;

			QString errorString = e.getMessage().c_str();

			SWGForensics::instance->printToConsole( errorString + " unable to open file " + file);

			return;
		} catch (...) {
			iffStream = NULL;

			SWGForensics::instance->printToConsole("unable to open file " + file);

			return;
		}

		/*QFile* qFile = new QFile(file);

		QString fileName = qFile->fileName();

		QString name = fileName.remove("D:/swg tres/");

		QString newName = "D:/filesforserver/" + name;

		if (!qFile->copy(newName)) {
			SWGForensics::instance->printToConsole("unable to copy file " + newName);
		}

		delete qFile;*/

		parse();
	}

	~FloorMesh() {
		delete iffStream;
	}

	void parse0006(uint32 next) {
		iffStream->openForm(next);

		Chunk* data = iffStream->openChunk('VERT');

		if (next == '0006') {
			int verticesSize = data->getUnsignedInt();

			for (int i = 0; i < verticesSize; ++i) {
				float x = iffStream->getFloat();
				float y = iffStream->getFloat();
				float z = iffStream->getFloat();


				vertices.append(Vert(x, y, z));
			}
		} else {
			int size = data->getChunkSize();

			while (size > 0) {
				float x = iffStream->getFloat();
				float y = iffStream->getFloat();
				float z = iffStream->getFloat();


				vertices.append(Vert(x, y, z));

				size -= 12;
			}
		}

		iffStream->closeChunk();

		Chunk* trisChunk = iffStream->openChunk('TRIS');

		//dont wanna know now

		if (next == '0006') {

			int trisCount = iffStream->getInt();

			for (int i = 0; i < trisCount; ++i) {
				Tri* tri = new Tri();

				tri->var1 = iffStream->getInt();
				tri->var2 = iffStream->getInt();
				tri->var3 = iffStream->getInt();
				tri->id = iffStream->getInt();
				tri->left = iffStream->getInt();
				tri->right = iffStream->getInt();
				tri->down = iffStream->getInt();
				tri->var8 = iffStream->getFloat();
				tri->var9 = iffStream->getFloat();
				tri->var10 = iffStream->getFloat();

				tri->var11 = iffStream->getByte();
				tri->var12 = iffStream->getByte();
				tri->var13 = iffStream->getByte();
				tri->var14 = iffStream->getByte();

				tri->var15 = iffStream->getInt();
				tri->var16 = iffStream->getInt();
				tri->var17 = iffStream->getInt();
				tri->var18 = iffStream->getInt();

				tris.append(tri);
			}

		} else {
			int trisSize = trisChunk->getChunkSize();

			while (trisSize > 0) {
				Tri* tri = new Tri();

				tri->var1 = iffStream->getInt();
				tri->var2 = iffStream->getInt();
				tri->var3 = iffStream->getInt();
				tri->id = iffStream->getInt();
				tri->left = iffStream->getInt();
				tri->right = iffStream->getInt();
				tri->down = iffStream->getInt();
				tri->var8 = iffStream->getFloat();
				tri->var9 = iffStream->getFloat();
				tri->var10 = iffStream->getFloat();

				tri->var11 = iffStream->getByte();
				tri->var12 = iffStream->getByte();
				tri->var13 = iffStream->getByte();
				tri->var14 = iffStream->getByte();

				tri->var15 = iffStream->getInt();
				tri->var16 = iffStream->getInt();
				tri->var17 = iffStream->getInt();
				tri->var18 = iffStream->getInt();

				tris.append(tri);

				trisSize -= 60;
			}
		}

		for (int i = 0; i < tris.size(); ++i) {
			Tri* tri = tris.at(i);

			Vector3 trisv[3];

			trisv[0] = vertices.at(tri->var1).getPos();
			trisv[1] = vertices.at(tri->var2).getPos();
			trisv[2] = vertices.at(tri->var3).getPos();

			tri->set(trisv);

			if (tri->left != -1) {
				tri->neighbors.add(tris.at(tri->left));
			}

			if (tri->right != -1) {
				tri->neighbors.add(tris.at(tri->right));
			}

			if (tri->down != -1) {
				tri->neighbors.add(tris.at(tri->down));
			}

			/*tri->id = iffStream->getInt();
			tri->left = iffStream->getInt();
			tri->right = iffStream->getInt();
			tri->down = iffStream->getInt();

			Vector3

			tris.append(tri);*/
		}

		iffStream->closeChunk();

		uint32 nextForm = 0;

		try {
			nextForm = iffStream->getNextFormType();
		} catch (...) {

		}

		if (nextForm == 'BTRE') {
			iffStream->openForm('BTRE');

			iffStream->openForm('0000');

			iffStream->openChunk('NODS');

			int nodeSize = iffStream->getInt();

			for (int i = 0; i < nodeSize; ++i) {
				Nods nods;
				nods.x1 = iffStream->getFloat();
				nods.y1 = iffStream->getFloat();
				nods.z1 = iffStream->getFloat();

				nods.x2 = iffStream->getFloat();
				nods.y2 = iffStream->getFloat();
				nods.z2 = iffStream->getFloat();

				nods.var1 = iffStream->getInt(); //id
				nods.var2 = iffStream->getInt(); //var2
				nods.var3 = iffStream->getInt(); //left
				nods.var4 = iffStream->getInt(); //rightnode

				nodes.append(nods);

				AABBNode* aabbNode = new AABBNode();
				Vector3 min(nods.x1, nods.y1, nods.z1);
				Vector3 max(nods.x2, nods.y2, nods.z2);

				aabbNode->getMbox()->setMinBound(min);
				aabbNode->getMbox()->setMaxBound(max);

				aabbNodes.append(aabbNode);
			}

			iffStream->closeChunk();

			iffStream->closeForm('0000');

			iffStream->closeForm('BTRE');
		}

		iffStream->openChunk('BEDG');

		int edgeSize = iffStream->getInt();

		for (int i = 0; i < edgeSize; ++i) {
			Bedg bedg;

			bedg.var1 = iffStream->getInt();
			bedg.var2 = iffStream->getInt();
			bedg.var3 = iffStream->getByte();

			edges.append(bedg);
		}

		iffStream->closeChunk('BEDG');

		if (iffStream->getRemainingSubChunksNumber() > 0) {

			nextForm = iffStream->getNextFormType();

			if (nextForm == 'PGRF') {

				iffStream->openForm('PGRF');

				iffStream->openForm('0001');

				iffStream->openChunk('META');

				int unkownMetaInt = iffStream->getInt();

				iffStream->closeChunk('META');

				iffStream->openChunk('PNOD');

				int nodesSize = iffStream->getInt();

				for (int i = 0; i < nodesSize; ++i) {
					PathNode pathNode;

					pathNode.var1 = iffStream->getInt();
					pathNode.var2 = iffStream->getInt();
					pathNode.var3 = iffStream->getInt();
					pathNode.var4 = iffStream->getInt();

					pathNode.var5 = iffStream->getFloat();
					pathNode.var6 = iffStream->getFloat();
					pathNode.var7 = iffStream->getFloat();
					pathNode.var8 = iffStream->getFloat();

					pathNodes.append(pathNode);
				}

				iffStream->closeChunk('PNOD');

				iffStream->openChunk('PEDG');

				int pathEdgeSize = iffStream->getInt();

				for (int i = 0; i < pathEdgeSize; ++i) {
					PathEdge pathEdge;

					pathEdge.var1 = iffStream->getInt();
					pathEdge.var2 = iffStream->getInt();
					pathEdge.var3 = iffStream->getInt();
					pathEdge.var4 = iffStream->getInt();

					pathEdges.append(pathEdge);
				}

				iffStream->closeChunk('PEDG');

				iffStream->openChunk('ECNT');

				int ecntSize = iffStream->getInt();

				for (int i = 0; i < ecntSize; ++i) {
					ecnt.append(iffStream->getInt());
				}

				iffStream->closeChunk('ECNT');

				iffStream->openChunk('ESTR');

				int estrSize = iffStream->getInt();

				for (int i = 0; i < estrSize; ++i) {
					estr.append(iffStream->getInt());
				}

				iffStream->closeChunk('ESTR');

				iffStream->closeForm('0001');

				iffStream->closeForm('PGRF');
			}
		}

		iffStream->closeForm(next);
	}

	void parse() {
		try {
			iffStream->openForm('FLOR');

			unsigned int nextFlorVersion = iffStream->getNextFormType();

			if (nextFlorVersion == '0006') {
				parse0006(nextFlorVersion);
			} else if (nextFlorVersion == '0005') {
				parse0006(nextFlorVersion);
			} else {
				QString err;
				QTextStream stream(&err);

				stream << "unkown floor version 0x" << hex << nextFlorVersion;
				stream << iffStream->getFileName().c_str();
				SWGForensics::instance->printToConsole(err);
			}

			iffStream->closeForm('FLOR');
		}  catch (Exception& e) {
			QString errorString = e.getMessage().c_str();

			SWGForensics::instance->printToConsole( errorString + " unable to parse file " + iffStream->getFileName().c_str());

			return;
		} catch (...) {
			QString err = "unable to parse file ";
			err += iffStream->getFileName().c_str();
			SWGForensics::instance->printToConsole(err);
		}
	}

	void printToConsole() {
		SWGForensics::instance->printToConsole("Vertices");

		QString size;
		QTextStream sizeStream(&size);

		sizeStream << "size:" << vertices.size();

		SWGForensics::instance->printToConsole(size);

		for (int i = 0; i < vertices.size(); ++i) {
			QString err;
			QTextStream stream(&err);

			const Vert* vert = &vertices.at(i);

			stream << "id: " << i << " x:" << vert->x << " y:" << vert->y << " z:" << vert->z;

			SWGForensics::instance->printToConsole(err);
		}

		SWGForensics::instance->printToConsole("Tris");

		QString trisSize;
		QTextStream trisSizeStream(&trisSize);

		trisSizeStream << "size:" << tris.size();

		SWGForensics::instance->printToConsole(trisSize);

		for (int i = 0; i < tris.size(); ++i) {
			Tri* tri = tris.at(i);

			tri->printToConsole();
		}

		SWGForensics::instance->printToConsole("Nods");

		QString nodsSize;
		QTextStream nodesSizeStream(&nodsSize);

		nodesSizeStream << "size:" << nodes.size();

		SWGForensics::instance->printToConsole(nodsSize);

		for (int i = 0; i < nodes.size(); ++i) {
			QString err;
			QTextStream stream(&err);

			const Nods* vert = &nodes.at(i);

			stream << "x1:" << vert->x1 << " y1:" << vert->y1 << " z1:" << vert->z1 << endl;
			stream << "x2:" << vert->x2 << " y2:" << vert->y2 << " z2:" << vert->z2 << endl;
			stream << "var1: " << vert->var1 << " var2: " << vert->var2 << " var3:" << vert->var3 << " var4: " << vert->var4;

			/*stream << "" << vert->x1 << " " << vert->y1 << " " << vert->z1 << endl;
			stream << "" << vert->x2 << " " << vert->y2 << " " << vert->z2 << endl;
			stream << "distance between points " << sqrt((vert->x2 - vert->x1) * (vert->x2 - vert->x1) + (vert->y2 - vert->y1) * (vert->y2 - vert->y1) + (vert->z2 - vert->z1) * (vert->z2 - vert->z1));
			stream << " " << vert->var1 << " " << vert->var2 << " " << vert->var3 << " " << vert->var4 << endl;*/

			SWGForensics::instance->printToConsole(err);
		}

		SWGForensics::instance->printToConsole("BEDG");

		QString bedgSize;
		QTextStream bedgSizeStream(&bedgSize);

		bedgSizeStream << "size:" << edges.size();

		SWGForensics::instance->printToConsole(bedgSize);

		for (int i = 0; i < this->edges.size(); ++i) {
			const Bedg* vert = &edges.at(i);

			vert->printToConsole();
		}

		SWGForensics::instance->printToConsole("pathNodes");

		QString pathNodesSize;
		QTextStream pathNodesSizeStream(&pathNodesSize);

		pathNodesSizeStream << "size:" << pathNodes.size();

		SWGForensics::instance->printToConsole(pathNodesSize);

		for (int i = 0; i < this->pathNodes.size(); ++i) {
			const PathNode* vert = &pathNodes.at(i);

			vert->printToConsole();
		}

		SWGForensics::instance->printToConsole("pathEdges");

		QString pathEdgesSize;
		QTextStream pathEdgesSizeStream(&pathEdgesSize);

		pathEdgesSizeStream << "size:" << pathEdges.size();

		SWGForensics::instance->printToConsole(pathEdgesSize);

		for (int i = 0; i < this->pathEdges.size(); ++i) {
			const PathEdge* vert = &pathEdges.at(i);

			vert->printToConsole();
		}

		SWGForensics::instance->printToConsole("ECNT");

		QString ecntSize;
		QTextStream ecntSizeStream(&ecntSize);

		ecntSizeStream << "size:" << ecnt.size();

		SWGForensics::instance->printToConsole(pathEdgesSize);

		for (int i = 0; i < this->ecnt.size(); ++i) {
			int var = ecnt.at(i);

			QString val;
			QTextStream stream(&val);

			stream << var;

			SWGForensics::instance->printToConsole(val);
		}

		SWGForensics::instance->printToConsole("ESTR");

		for (int i = 0; i < this->estr.size(); ++i) {
			int var = estr.at(i);

			QString val;
			QTextStream stream(&val);

			stream << var;

			SWGForensics::instance->printToConsole(val);
		}
	}

};

#endif /* FLOORMESH_H_ */
