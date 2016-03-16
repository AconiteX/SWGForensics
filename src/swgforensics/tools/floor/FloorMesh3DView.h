/*
 * FloorMesh3DView.h
 *
 *  Created on: 04/12/2010
 *      Author: TheAnswer
 */

#ifndef FLOORMESH3DVIEW_H_
#define FLOORMESH3DVIEW_H_


#include <QGLWidget>


class FloorMeshAnalizer;
class FloorMesh;
class MeshAppearanceTemplate;
class AABBNode;
class PortalLayout;
class Tri;

#include "src/system/util/Matrix4.h"
#include "src/system/util/Vector3.h"

#include <QGraphicsSceneMouseEvent>

class FloorMesh3DView : public QGLWidget
{
public:
	FloorMesh3DView(FloorMeshAnalizer* analizer, QWidget *parent = 0);
    ~FloorMesh3DView();

    const static float MAP_SCALE = 10.f;
    const static float MAP_Z = 64;
    const static float MAP_X = 64;

    void recalculateTerrain() {
    	initializeTerrain();
    	updateGL();
    }

    void addFloorMesh(FloorMesh* mesh) {
        floorMeshes.append(mesh);
        calculatedPath.clear();
        calculatePath(1, 10);
        calculateAABBs();
    }

    void addMeshAppearance(MeshAppearanceTemplate* m) {
        meshAppearances.append(m);
        calculateAABBs();
    }

    void addPortalLayout(PortalLayout* portal) {
    	portalLayouts.append(portal);
    }

    void clearFloorMeshes() {
        floorMeshes.clear();
    }

    void clearMeshAppearance() {
        meshAppearances.clear();
    }

    void rotateMesh(float rad);


    void calculatePath(int tri1, int tri2);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *);// { /*setAnimationPaused(true);*/ }
    void mouseReleaseEvent(QMouseEvent *) { /*setAnimationPaused(false); */}

    void keyPressEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* mouseEvent);

    void calculateAABBs();
    void drawAABBNode(AABBNode* node);
    void drawAABBTrees();
    void drawBEDG();

private:
    void initCommon();
    void initializeTerrain();
    void initializeTexture();

    //qreal aspect;
    GLuint terrainTexture;
    float angle;
    float radians;

    float mouseY;

    float lastMouseX, lastMouseY;

    float cameraX, cameraZ, cameraY;
    float lookX, lookY, lookZ;

    FloorMeshAnalizer* analizer;
    QVector<FloorMesh*> floorMeshes;
    QVector<MeshAppearanceTemplate*> meshAppearances;
    QVector<AABBNode*> aabbTree;
    QVector<PortalLayout*> portalLayouts;
    Matrix4 worldMatrix;

    QVector<Tri*> calculatedPath;
    QVector<Vector3> funnelPath;
    //GLuint cubeTexture;
    //bool hasDynamicTextureUpdate;

    bool update;


};
//! [3]

#endif /* FLOORMESH3DVIEW_H_ */
