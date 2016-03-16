#ifndef BOUNDARYRECTANGLE_H
#define BOUNDARYRECTANGLE_H

#include "Mfrc.h"

class BoundaryRectangle {
protected:
    float x0, x1, y0, y1;
    int featheringType;
    float featheringAmount;

    float newX0, newX1, newY0, newY1;

public:

    BoundaryRectangle() {
        x0 = -64.46579;
        y0 = 40.3267;
        x1 = -32.53421;
        y1 = 107.673286;

        featheringType = 0;
        featheringAmount = 1;

        initialize();
    }

    int initialize() {
      double v1; // fst7@2
      double v2; // fst7@4
      float *v3; // eax@5
      double v4; // fst7@5
      int result; // eax@7
      double v6; // fst7@7
      double v7; // fst7@7
      float v8; // [sp+0h] [bp-8h]@5
      float v9; // [sp+4h] [bp-4h]@5

      if ( x0 > x1 ) {
        v1 = x0;
        x0 = x1;
        x1 = v1;
      }

      if ( y0 > y1 ) {
        v2 = y0;
        y0 = y1;
        y1 = v2;
      }

      v9 = x1 - x0;
      v4 = y1 - y0;
      v8 = v4;
      v3 = &v8;
      if ( v4 >= v9 )
        v3 = &v9;
      v6 = featheringAmount * *v3;
      result = 0;
      v7 = v6 * 0.5;
      newX0 = x0;
      newY0 = y0;
      newX1 = x1;
      newY1 = y1;

      newX0 = v7 + newX0;
      newY0 = v7 + newY0;
      newX1 = newX1 - v7;
      newY1 = newY1 - v7;
      return result;
    }

    float process2(float x, float y);
    float process(float a2, float a3);


};

#endif // BOUNDARYRECTANGLE_H
