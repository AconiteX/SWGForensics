#include "floormeshanalizer.h"

#include <QFileDialog>

#include "../../swgforensics.h"

#include "../objects/objectstolua/floormesh/FloorMesh.h"
#include "../objects/objectstolua/params/PortalLayout.h"
#include "../objects/objectstolua/mesh/MeshAppearanceTemplate.h"

#include <QGraphicsTextItem>

#include "FloorMesh3DView.h"


FloorMeshAnalizer::FloorMeshAnalizer(QWidget *parent)
: QWidget(parent) {
	ui.setupUi(this);

	ui.graphicsView->setScene(&scene);

	scene.clear();

	ui.graphicsView->show();

	view = new FloorMesh3DView(this);

	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(openFloorMesh()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(clearScene()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(openPortalLayout()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(openMeshAppearance()));
}

FloorMeshAnalizer::~FloorMeshAnalizer() {

}

void FloorMeshAnalizer::openMeshAppearance() {
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isEmpty())
		return;

	//clearScene();

	MeshAppearanceTemplate* mesh = new MeshAppearanceTemplate(fileName);

	//delete mesh;

	//view->rotateMesh(5.4105206);

	view->addMeshAppearance(mesh);



	view->show();
}


void FloorMeshAnalizer::openPortalLayout() {
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isEmpty())
		return;

	clearScene();

	QVector<FloorMesh*> meshes;
	QVector<MeshAppearanceTemplate*> appMeshes;

	PortalLayout* portal = new PortalLayout(fileName, meshes, appMeshes);

	for (int i = 0; i < meshes.size(); ++i) {
		FloorMesh* mesh = meshes.at(i);

		view->addFloorMesh(mesh);
		//draw2dScene(mesh);
	}

	for (int i = 0; i < appMeshes.size(); ++i) {
		MeshAppearanceTemplate* templ = appMeshes.at(i);

		view->addMeshAppearance(templ);
	}

	view->addPortalLayout(portal);

	view->show();
}

void FloorMeshAnalizer::draw2dScene(FloorMesh* mesh) {
	for (int i = 0; i < mesh->vertices.size(); ++i) {
		const Vert* vert = &mesh->vertices.at(i);
		//const Vert* vert2 = &mesh->vertices.at(i + 1);

		//scene.addLine ( vert->x * 20, vert->z * 20, vert2->x * 20, vert2->z * 20);

		//++i;

		scene.addEllipse (vert->x * 20, vert->z * 20, 3, 3, QPen(), QBrush ( QColor(0, 255, 0)));

	}

	//lets connect the vertices
	for (int i = 0; i < mesh->tris.size(); ++i) {
		Tri* tri = mesh->tris.at(i);

		int pointA = tri->var1;
		int pointB = tri->var2;
		int pointC = tri->var3;
		//int pointD = tri->var4;

		const Vert* vert = &mesh->vertices.at(pointA);
		const Vert* vert2 = &mesh->vertices.at(pointB);
		const Vert* vert3 = &mesh->vertices.at(pointC);
		//const Vert* vert4 = &mesh->vertices.at(pointD);

		scene.addLine ( vert->x * 20, vert->z * 20, vert2->x * 20, vert2->z * 20);
		scene.addLine ( vert2->x * 20, vert2->z * 20, vert3->x * 20, vert3->z * 20);
		scene.addLine ( vert3->x * 20, vert3->z * 20, vert->x * 20, vert->z * 20);
	}

	//lets paint the path graph

	for (int i = 0; i < mesh->pathEdges.size(); ++i) {
		const PathEdge* pathEdge = &mesh->pathEdges.at(i);

		int from = pathEdge->var1;
		int to = pathEdge->var2;

		const PathNode* fromNode = &mesh->pathNodes.at(from);
		const PathNode* toNode = &mesh->pathNodes.at(to);

		QPen qpen(QColor(0, 0, 255));
		scene.addLine (fromNode->var5 * 20, fromNode->var7 * 20, toNode->var5 * 20, toNode->var7 * 20, qpen);
	}

}

void FloorMeshAnalizer::openFloorMesh() {
	QString fileName = QFileDialog::getOpenFileName(this);

	if (fileName.isEmpty())
		return;

	FloorMesh* mesh = new FloorMesh(fileName);

	draw2dScene(mesh);

	mesh->printToConsole();

	view->addFloorMesh(mesh);
	view->show();

	//delete mesh;
}

void FloorMeshAnalizer::clearScene() {
	scene.clear();
	view->clearFloorMeshes();
	view->clearMeshAppearance();
}
