#ifndef BOUNDARYCIRCLE_H
#define BOUNDARYCIRCLE_H

#include "Mfrc.h"

class BoundaryCircle {
    float centerX, centerY, radius, radiusSquared, featheringAmount;
    int featheringType;

public:

    long double process(float a2, float a3)
    {
      long double v3; // fst7@1
      long double v4; // fst6@1
      long double result; // fst7@2
      long double v6; // fst7@3
      long double v7; // fst7@3
      float v8; // [sp+8h] [bp+8h]@1

      v3 = centerX - a2;
      v4 = centerY - a3;
      v8 = v4 * v4 + v3 * v3;
      if ( v8 <= radiusSquared )
      {
        v7 = (1.0 - featheringAmount) * readius;
        v6 = v7 * v7;
        if ( v8 > v6 )
          result = 1.0 - (v8 - v6) / (radiusSquared - v6);
        else
          result = 1.0;
      }
      else
      {
        result = 0.0;
      }
      return result;
    }


    void inici(int n, int a[NMAX][NMAX], unsigned int llavor) {
        int i = 0, j = 0;

        srand(llavor);

        for (i = 0; i < n; i++) {
            for (j = 0; j  < n; j++) {
                a[i][j] = rand() % 2;
            }
        }
    }

    int nou(int n, int a[NMAX][NMAX], int i, int j) {
        int valorVell = a[i][j];
        int vius = 0;

        for (int x = i - 1; x < i + 2; ++x) {
            if (x >= 0 && x < n) {
                for (int y = j - 1; y < j + 2; ++y) {
                    if (y >= 0 && y < n) {
                        if (i != x && y != j) {
                            if (a[x][y] == 1)
                                vius++;
                        }
                    }
                }
            }
        }

        if (valorVell == 1) {
            if (vius == 2 || vius == 3) {
                return 1;
            }
        } else if (valorVell == 0) {
            if (vius == 2)
                return 1;
        }

        return 0;
    }

    void evolucio(int n, int a[NMAX][NMAX], int b[NMAX][NMAX]) {
        int i = 0, j = 0;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                b[i][j] = nou(n, a, i, j);
            }
        }
    }

    void test() {
        int n = 0, llavor = 0, itMax = 0;
        int matriu[NMAX][NMAX];

        srand(llavor);
    }

};

#endif // BOUNDARYCIRCLE_H
