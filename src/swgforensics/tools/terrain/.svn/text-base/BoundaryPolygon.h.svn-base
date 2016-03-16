#ifndef BOUNDARYPOLYGON_H
#define BOUNDARYPOLYGON_H

#include <QVector>

class Point2D {
public:
    Point2D() {

    }

    float x, y;
};

class BoundaryPolygon {
    QVector<Point2D> points;
    float minX, minY, maxX, maxY;

    float featheringAmount;

public:
    BoundaryPolygon() {
        minX = 800000000;
        minY = 800000000;
        maxX = -8000000000;
        maxY = -8000000000;

        Point2D point;
        point.x = -55.08557;
        point.y = 33.56522;

        points.append(point);

        point.x = -50.5;
        point.y = 35.75;

        points.append(point);

        point.x = -45.25;
        point.y = 33.25;

        points.append(point);

        point.x = -41.25;
        point.y = 26.75;

        points.append(point);

        point.x = -45.5;
        point.y = 18;

        points.append(point);

        point.x = -49.75;
        point.y = 11.5;

        points.append(point);

        point.x = -51;
        point.y = 2.25;

        points.append(point);

        point.x = -55;
        point.y = -4.25;

        points.append(point);

        point.x = -61.5;
        point.y = -5.5;

        points.append(point);

        point.x = -69;
        point.y = -5.5;

        points.append(point);

        point.x = -72.75;
        point.y = -3;

        points.append(point);

        point.x = -74;
        point.y = 2.5;

        points.append(point);

        point.x = -70.75;
        point.y = 7.5;

        points.append(point);

        point.x = -65.75;
        point.y = 10.5;

        points.append(point);

        point.x = -65.15062;
        point.y = 15.72441;

        points.append(point);

        point.x = -64.52232;
        point.y = 22.06689;

        points.append(point);

        point.x = -60.14131;
        point.y = 25.7342;

        points.append(point);

        point.x = -53.91499;
        point.y = 28.99825;

        points.append(point);

        featheringAmount = 7;

        initialize();
    }

    void initialize() {
        for(int i = 0; i < points.size(); ++i) {
            const Point2D* point = &points.at(i);

            if (point->x < minX)
                minX = point->x;

            if (point->y < minY)
                minY = point->y;

            if (point->x > maxX)
                maxX = point->x;

            if (point->y > maxY)
                maxY = point->y;
        }
    }

    double process(float x, float y);
    double process2(float x, float y);


};

#endif // BOUNDARYPOLYGON_H
