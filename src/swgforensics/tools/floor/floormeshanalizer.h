#ifndef FLOORMESHANALIZER_H
#define FLOORMESHANALIZER_H

#include <QtGui/QWidget>
#include "ui_floormeshanalizer.h"

class FloorMesh3DView;
class FloorMesh;

class FloorMeshAnalizer : public QWidget {
    Q_OBJECT

public:
    FloorMeshAnalizer(QWidget *parent = 0);
    ~FloorMeshAnalizer();

public slots:
    void openFloorMesh();
    void openMeshAppearance();
    void clearScene();
    void openPortalLayout();
    void draw2dScene(FloorMesh* mesh);

private:
    Ui::FloorMeshAnalizerClass ui;
    QGraphicsScene scene;
    FloorMesh3DView* view;
};

#endif // FLOORMESHANALIZER_H
