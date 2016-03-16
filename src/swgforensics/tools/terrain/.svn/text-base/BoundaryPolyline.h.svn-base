#ifndef BOUNDARYPOLYLINE_H
#define BOUNDARYPOLYLINE_H

#include "BoundaryPolygon.h"
#include "Mfrc.h"

typedef unsigned char uint8;
typedef signed short int16;


class BoundaryPolyline {
    QVector<Point2D> points;
    float minX, minY, maxX, maxY;

    float featheringAmount;

    float lineWidth;
public:

    BoundaryPolyline() {
        minX = 800000000;
        minY = 800000000;
        maxX = -8000000000;
        maxY = -8000000000;

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

        minX = minX - lineWidth;
        maxX = maxX + lineWidth;
        minY = minY - lineWidth;
        maxY = maxY + lineWidth;
    }

    double process(float x, float y){
        if (x < minX)
            return 0.0;

        if (x > maxX || y < (double)minY )
            return 0.0;

        if ( y > maxY )
            return 0.0;

        double v16 = lineWidth * lineWidth;
        double v21 = 0;

        double v31 = v16;
        double v20, v19;

        double result = 0;

        for (int i = 0; i < points.size(); ++i) {
            const Point2D* point = &points.at(i);

            v20 = y - point->y;
            v19 = v20 * v20 + (x - point->x) * (x - point->x);
            if ( v19 < v16 ) {
                v21 = v19;
                v16 = v21;
            }
        }

        double v33, v35, v36, v26, v27, v25, v24, v28;

        for (int i = 0; i < points.size() - 1; ++i) {
            const Point2D* point = &points.at(i);
            const Point2D* point2 = &points.at(i + 1);

            v35 = point2->x - point->x;
            v24 = point2->y -  point->y;
            v33 = v24;
            v36 = ((y -  point->y) * v33 + (x - point->x) * v35) / (v24 * v24 + v35 * v35);
            if ( v36 >= 0.0 ) {
                if ( v36 <= 1.0 ) {
                    v26 = x - (v35 * v36 + point->x);
                    v27 = y - (v33 * v36 +  point->y);
                    v25 = v27 * v27 + v26 * v26;

                    if ( v25 < v16 ) {
                        v28 = v25;
                        v16 = v28;
                    }
                }
            }

        }

        if ( v16 >= v31 )
            return 0.0;

        double v29 = (1.0 - featheringAmount) * lineWidth;

        if ( v16 >= v29 * v29 )
            result = 1.0 - (sqrt(v16) - v29) / (lineWidth - v29);
        else
            result = 1.0;

        return result;
    }



};

#endif // BOUNDARYPOLYLINE_H
