/*
 * glwidget.cpp
 *
 *  Created on: 06/04/2010
 *      Author: TheAnswer
 */


#include "glwidget.h"
#include <math.h>

#include "AffectorHeightFractal.h"
#include "TerrainAnalizer.h"

GLWidget::GLWidget(TerrainAnalizer* analizer, QWidget *parent) : QGLWidget() {
    setWindowTitle(tr("Terrain Analizer 3D View"));

    angle = 0;
    radians = 0;
    mouseY = 150;

    this->analizer = analizer;
}

GLWidget::~GLWidget() {

}

void GLWidget::initializeGL() {
    makeCurrent();
    initializeTerrain();
    initCommon();

    QImage tex, buf;
    if ( !buf.load( "green.bmp" ) ) {
    	qWarning( "Could not read image file, using single-color instead." );
    	/*QImage dummy( 128, 128, 32 );
    	dummy.fill( Qt::green.rgb() );
    	buf = dummy;*/
    } else {
        qWarning( "loaded green shit" );
    }

    tex = QGLWidget::convertToGLFormat( buf );

    glGenTextures(1, &terrainTexture);
    glBindTexture(GL_TEXTURE_2D, terrainTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, tex.width(), tex.height(), GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
	int key = event->key();

	switch (key) {
	case Qt::Key_S:
		mouseY += 20;
		break;
	case Qt::Key_W:
		mouseY -= 20;
		break;
	case Qt::Key_A:
		angle += 3.0f;
		break;
	case Qt::Key_D:
		angle -= 3.0f;
		break;
	default:
		//QFrame::keyPressEvent(event);
		break;
	}

	updateGL();
}

void GLWidget::paintGL() {
    makeCurrent();

    //angle = 0.f;

    radians =  float(M_PI*(angle-90.0f)/180.0f);

    // calculate the camera look-at coordinates as the center of the terrain map
    lookX = (MAP_X*MAP_SCALE)/2.0f;
    lookY = 150.f * 2;
    lookZ = -(MAP_Z*MAP_SCALE)/2.0f;

    // calculate the camera's position
    cameraX = lookX + sin(radians)*mouseY;	   // multiplying by mouseY makes the
    cameraZ = lookZ + cos(radians)*mouseY;    // camera get closer/farther away with mouseY
    cameraY = lookY + mouseY / 2.0f;



    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // set the camera position
    gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);

    // set the current texture to the land texture
    glBindTexture(GL_TEXTURE_2D, terrainTexture);

    // we are going to loop through all of our terrain's data points,
    // but we only want to draw one triangle strip for each set along the x-axis.
    for (int z = 0; z < MAP_Z-1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = 0; x < MAP_X-1; x++)
        {
            // for each vertex, we calculate the grayscale shade color,
            // we set the texture coordinate, and we draw the vertex.
            /*
				   the vertices are drawn in this order:

				   0  ---> 1
				          /
					    /
				     |/
				   2  ---> 3
			 */

            // draw vertex 0
            glColor3f(terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f, terrain[x][z][1]/255.0f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(terrain[x][z][0], terrain[x][z][1], terrain[x][z][2]);

            // draw vertex 1
            glTexCoord2f(1.0f, 0.0f);
            glColor3f(terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f, terrain[x+1][z][1]/255.0f);
            glVertex3f(terrain[x+1][z][0], terrain[x+1][z][1], terrain[x+1][z][2]);

            // draw vertex 2
            glTexCoord2f(0.0f, 1.0f);
            glColor3f(terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f, terrain[x][z+1][1]/255.0f);
            glVertex3f(terrain[x][z+1][0], terrain[x][z+1][1], terrain[x][z+1][2]);

            // draw vertex 3
            glColor3f(terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f, terrain[x+1][z+1][1]/255.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(terrain[x+1][z+1][0], terrain[x+1][z+1][1], terrain[x+1][z+1][2]);
        }
        glEnd();
    }
    // enable blending
    glEnable(GL_BLEND);

    // enable read-only depth buffer
    glDepthMask(GL_FALSE);

    // set the blend function to what we use for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // set back to normal depth buffer mode (writable)
    glDepthMask(GL_TRUE);

    // disable blending
    glDisable(GL_BLEND);

    glFlush();
}


void GLWidget::initCommon() {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// clear to black

	glShadeModel(GL_SMOOTH);					   // use smooth shading
	glEnable(GL_DEPTH_TEST);					   // hidden surface removal
	glEnable(GL_CULL_FACE);						   // do not calculate inside of poly's
	glFrontFace(GL_CCW);						      // counter clock-wise polygons are out

	glEnable(GL_TEXTURE_2D);					   // enable 2D texturing
}

void GLWidget::initializeTerrain() {
	AffectorHeightFractal* ahfr = analizer->getAffectorHeightFractal();

	for (int z = 0; z < MAP_Z; z++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			terrain[x][z][0] = float(x) * MAP_SCALE;
			terrain[x][z][1] = ahfr->getHeight(x, z) * MAP_SCALE;//(float)imageData[(z*MAP_Z+x)*3];
			terrain[x][z][2] = -float(z) * MAP_SCALE;
		}
	}

}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);	   // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);		   // set projection matrix current matrix
    glLoadIdentity();					      // reset projection matrix

    // calculate aspect ratio of window
    gluPerspective(54.0f,(GLfloat)width/(GLfloat)height,1.0f,2000.0f);

    glMatrixMode(GL_MODELVIEW);			// set modelview matrix
    glLoadIdentity();					      // reset modelview matrix
    /*glViewport(0, 0, width, height);
    aspect = (qreal)width / (qreal)(height ? height : 1);
    perspectiveProjection();*/
}
