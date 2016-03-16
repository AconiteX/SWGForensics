
#include "BoundaryRectangle.h"
#include "BoundaryPolygon.h"
#include "BoundaryPolyline.h"

double BoundaryPolygon::process2(float x, float y) {
  const Point2D* lastPoint = NULL;

  double result = 0;

  if (x < minX)
      return 0.0;

  if (x > maxX || y < minY)
      return 0.0;

  if (y > maxY)
      return 0.0;

  int v16 = points.size();

  if (points.size() <= 0)
      return 0.0;

  bool v50 = 0;

  lastPoint = &points.at(points.size() - 1);

  for (int i = 0; i < points.size(); ++i) {
      const Point2D* point = &points.at(i);

      if ((point->y <= y && y < lastPoint->y) || (lastPoint->y <= y && y < point->y)) {
          if ( (y - point->y) * (lastPoint->x - point->x) / (lastPoint->y - point->y)
              + point->x > (double)x ) {

              v50 = v50 == 0;

          }
      }

      lastPoint = point;
  }


  double v25, v43;

  if (v50) {
    if (featheringAmount == 0.0)
      return 1.0;

    v25 = featheringAmount * featheringAmount;
    v43 = v25;
    double v27, v26, v28;

    for (int i = 0; i < points.size(); ++i) {
        const Point2D* point = &points.at(i);

        v27 = y - point->y;
        v26 = v27 * v27 + (x - point->x) * (x - point->x);

        if ( v26 < v25 ) {
            v28 = v26;
            v25 = v28;
        }

    }

    double v35, v36, v44, v45, v37, v38, v39, v40, v41;

    lastPoint = &points.at(points.size() - 1);

    for (int i = 0; i < points.size(); ++i) {
        const Point2D* point = &points.at(i);

        v35 = lastPoint->x - point->x;
        v36 = lastPoint->y - point->y;
        v44 = point->y - lastPoint->y;
        v45 = point->x - lastPoint->x;
        v37 = ((x - lastPoint->x) * v45 + (y - lastPoint->y) * v44) / (v36 * v36 + v35 * v35);
        if ( v37 >= 0.0 ) {
          if ( v37 <= 1.0 ) {
            v39 = x - (v45 * v37 + lastPoint->x);
            v40 = y - (v44 * v37 + lastPoint->y);
            v38 = v40 * v40 + v39 * v39;
            if ( v38 < v25 ) {
              v41 = v38;
              v25 = v41;
            }
          }
        }

        lastPoint = point;
    }

    if ( v25 >= v43 - 0.00009999999747378752 && v25 <= v43 + 0.00009999999747378752 )
      result = 1.0;
    else
      result = sqrt(v25) / featheringAmount;
  } else {
    result = 0.0;
  }

  return result;
}

double BoundaryPolygon::process(float x, float y) {

  double v3 = x;
  bool v9;
  bool v10, v13, v14, v12, v11;

  const Point2D* lastPoint = NULL;

  double result;

  if ( v3 >= minX ) {
      v9 = x < (double)maxX;
      v10 = x == maxX;
      goto LABEL_10;
  }
  return 0.0;

  if ( v3 < minX )
      return 0.0;
  v11 = x < (double)maxX;
  v12 = x == maxX;
  LABEL_15:
  if ( !(v11 | v12) || y < maxY )
      return 0.0;
  v13 = y < (double)minY;
  v14 = y == minY;
  goto LABEL_18;

  if ( v3 < maxX )
      return 0.0;
  v11 = x < (double)minX;
  v12 = x == minX;
  goto LABEL_15;

  if ( v3 < maxX )
    return 0.0;
  v9 = x < (double)minX;
  v10 = x == minX;
LABEL_10:
  if ( !(v9 | v10) || y < (double)minY )
    return 0.0;
  v13 = y < (double)maxY;
  v14 = y == maxY;
LABEL_18:
  if ( !(v13 | v14) )
    return 0.0;
  int v16 = points.size();
  bool v50 = 0;
  if ( v16 <= 0 )
    goto LABEL_48;

  lastPoint = &points.at(points.size() - 1);

  for (int i = 0; i < points.size(); ++i) {
      const Point2D* point = &points.at(i);

      if ((point->y <= y && y < lastPoint->y) || (lastPoint->y <= y && y < point->y)) {
          if ( (y - point->y) * (lastPoint->x - point->x) / (lastPoint->y - point->y)
              + point->x > (double)x ) {

              v50 = v50 == 0;

          }
      }

      lastPoint = point;
  }


  double v25, v43;

  if ( v50 ) {
    if ( featheringAmount == 0.0 )
      goto LABEL_49;
    v25 = featheringAmount * featheringAmount;
    v43 = v25;
    double v27, v26, v28;

    for (int i = 0; i < points.size(); ++i) {
        const Point2D* point = &points.at(i);

        v27 = y - point->y;
        v26 = v27 * v27 + (x - point->x) * (x - point->x);

        if ( v26 < v25 ) {
            v28 = v26;
            v25 = v28;
        }

    }


    double v49, v32, v47, v33, v34, v35, v36, v44, v45, v37, v38, v39, v40, v41, v48;

    lastPoint = &points.at(points.size() - 1);

    for (int i = 0; i < points.size(); ++i) {
        const Point2D* point = &points.at(i);

        v49 = lastPoint->x;//*(float *)(v31 + v17);
        v32 = lastPoint->y;//*(float *)(v31 + v17 + 4);
        v47 = v32;
        v33 = point->x;
        v34 = point->y;
        v35 = v49 - v33;
        v36 = v47 - v34;
        v44 = v34 - v47;
        v45 = v33 - v49;
        v37 = ((x - v49) * v45 + (y - v47) * v44) / (v36 * v36 + v35 * v35);
        v48 = v37;
        if ( v37 >= 0.0 )
        {
          if ( v48 <= 1.0 )
          {
            v39 = x - (v45 * v48 + v49);
            v40 = y - (v44 * v48 + v47);
            v38 = v40 * v40 + v39 * v39;
            if ( v38 < v25 )
            {
              v41 = v38;
              v25 = v41;
            }
          }
        }

        lastPoint = point;
    }

    if ( v25 >= v43 - 0.00009999999747378752 && v25 <= v43 + 0.00009999999747378752 )
LABEL_49:
      result = 1.0;
    else
      result = sqrt(v25) / featheringAmount;
  }
  else
  {
LABEL_48:
    result = 0.0;
  }
  return result;
}

float BoundaryRectangle::process2(float x, float y) {
    /*v3 = this;
                  if ( *(_BYTE *)(this + 60) ) initialized to 0
                  {
                    v31 = x;
                    v32 = y;
                    sub_ABB330(this + 64, (int)&v33, (int)&v31);
                    x = v33;
                    y = v34;
                  }*/

    if (!(x >= x0))
        return 0.0;

    if (!(x < (double)x1 | x == x1) || y < (double)y0)
        return 0.0;

    if (!(y < (double)y1 | y == y1))
        return 0.0;

    if (featheringAmount == 0.0)
        return 1.0;

    if (!(x < newX1 || x > newX0 || y < newY1 || y > newY0))
        return 1.0;

    float v36 = x - x0;
    float v35 = x1 - x;
    float v34 = y - y0;
    y = y1 - y;
    x = x1 - x0;
    float v28 = y1 - y0;
    float v32 = v28;
    float* v27 = &v32;
    if ( v28 >= x )
        v27 = &x;

    float v30 = featheringAmount * *v27 * 0.5;
    float v29 = v30;
    if ( v36 < v30 )
        v29 = v36;
    if ( v35 < v29 )
        v29 = v35;
    if ( v34 < v29 )
        v29 = v34;
    if ( y < v29 )
        v29 = y;

    return v29 / v30;
}



float BoundaryRectangle::process(float a2, float a3) {
  int v3; // esi@1
  double v4; // fst7@3
  unsigned __int8 v5; // c0@3
  unsigned __int8 v6; // c2@3
  __int16 v7; // fps@3
  char v8; // ah@3
  __int16 v9; // fps@3
  unsigned __int8 v10; // c0@6
  unsigned __int8 v11; // c3@6
  unsigned __int8 v12; // c0@8
  unsigned __int8 v13; // c3@8
  unsigned __int8 v14; // c0@14
  unsigned __int8 v15; // c3@14
  long double v17; // fst7@24
  //unsigned __int8 v18; // c0@24
  //unsigned __int8 v19; // c2@24
  __int16 v20; // fps@24
  char v21; // ah@24
  __int16 v22; // fps@24
  unsigned __int8 v23; // c0@27
  unsigned __int8 v24; // c3@27
  unsigned __int8 v25; // c0@31
  unsigned __int8 v26; // c3@31
  float *v27; // eax@33
  double v28; // fst7@33
  double v29; // fst6@35
  double v30; // fst7@35
  float v31; // [sp+4h] [bp-18h]@2
  float v32; // [sp+8h] [bp-14h]@2
  float v33; // [sp+Ch] [bp-10h]@2
  float v34; // [sp+10h] [bp-Ch]@2
  float v35; // [sp+14h] [bp-8h]@33
  float v36; // [sp+18h] [bp-4h]@33

  /*v3 = this;
  if ( *(_BYTE *)(this + 60) ) initialized to 0
  {
    v31 = a2;
    v32 = a3;
    sub_ABB330(this + 64, (int)&v33, (int)&v31);
    a2 = v33;
    a3 = v34;
  }*/
  v7 = 0;
  v8 = 0;
  v4 = a2;

  v9 = 0;

  if ( v4 >= x0 ) {
      v10 = a2 < (long double)x1;
      v11 = a2 == x1;
      goto LABEL_12;
  }
  return 0.0;

  if ( v4 < x0 )
      return 0.0;
  v12 = a2 < (long double)x1;
  v13 = a2 == x1;
  LABEL_17:
  if ( !(v12 | v13) || a3 < (long double)y1 )
      return 0.0;
  v14 = a3 < (long double)y0;
  v15 = a3 == y0;
  goto LABEL_20;



  if ( v4 < x1 )
      return 0.0;
  v12 = a2 < (long double)x0;
  v13 = a2 == x0;
  goto LABEL_17;


  if ( v4 < x1 )
      return 0.0;
  v10 = a2 < (long double)x0;
  v11 = a2 == x0;
  LABEL_12:
  if ( !(v10 | v11) || a3 < (long double)y0 )
      return 0.0;
  v14 = a3 < (long double)y1;
  v15 = a3 == y1;
  LABEL_20:
  if ( !(v14 | v15) )
      return 0.0;
  if ( featheringAmount == 0.0 )
      return 1.0;
  v20 = 0;
  v21 = 0;
  v17 = a2;

  v22 = 0;

  if ( v17 < newX1 || a2 > newX0 || a3 < newY1 || a3 > newY0 )
      goto LABEL_33;
  return 1.0;

  if ( v17 < newX1 )
      goto LABEL_33;
  v23 = a2 < (long double)newX0;
  v24 = a2 == newX0;
  goto LABEL_47;



  if ( v17 < newX0 || a2 > (long double)newX1 || a3 < (long double)newY1 )
      goto LABEL_33;
  v25 = a3 < (long double)newY0;
  v26 = a3 == newY0;
  goto LABEL_32;


  if ( v17 >= newX0 ) {
      v23 = a2 < (long double)newX1;
      v24 = a2 == newX1;
      LABEL_47:
      if ( !(v23 | v24) || a3 < (long double)newY0 )
          goto LABEL_33;
      v25 = a3 < (long double)newY1;
      v26 = a3 == newY1;
      LABEL_32:
      if ( !(v25 | v26) )
          goto LABEL_33;
      return 1.0;
  }
  LABEL_33:
  v36 = a2 - x0;
  v35 = x1 - a2;
  v34 = a3 - y0;
  a3 = y1 - a3;
  a2 = x1 - x0;
  v28 = y1 - y0;
  v32 = v28;
  v27 = &v32;
  if ( v28 >= a2 )
      v27 = &a2;
  v30 = featheringAmount * *v27 * 0.5;
  v29 = v30;
  if ( v36 < v30 )
      v29 = v36;
  if ( v35 < v29 )
      v29 = v35;
  if ( v34 < v29 )
      v29 = v34;
  if ( a3 < v29 )
      v29 = a3;
  return v29 / v30;
}
