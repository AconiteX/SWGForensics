/*
 * glwidget.h
 *
 *  Created on: 06/04/2010
 *      Author: TheAnswer
 */

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>


class TerrainAnalizer;

class GLWidget : public QGLWidget
{
public:
    GLWidget(TerrainAnalizer* analizer, QWidget *parent = 0);
    ~GLWidget();

    const static float MAP_SCALE = 10.f;
    const static float MAP_Z = 512;
    const static float MAP_X = 512;

    void recalculateTerrain() {
    	initializeTerrain();
    	updateGL();
    }

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *) { /*setAnimationPaused(true);*/ }
    void mouseReleaseEvent(QMouseEvent *) { /*setAnimationPaused(false); */}

    void keyPressEvent(QKeyEvent* event);

private:
    void initCommon();
    void initializeTerrain();
    void initializeTexture();

    //qreal aspect;
    GLuint terrainTexture;
    float terrain[512][512][3];		// heightfield terrain data (0-255); 256x256
    float angle;
    float radians;

    float mouseY;

    float cameraX, cameraZ, cameraY;
    float lookX, lookY, lookZ;

    TerrainAnalizer* analizer;
    //GLuint cubeTexture;
    //bool hasDynamicTextureUpdate;


};
//! [3]


#endif /* GLWIDGET_H_ */
