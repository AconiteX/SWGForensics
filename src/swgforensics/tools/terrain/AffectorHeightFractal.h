/*
 * AffectorHeightFractal.h
 *
 *  Created on: 04/04/2010
 *      Author: TheAnswer
 */

#ifndef AFFECTORHEIGHTFRACTAL_H_
#define AFFECTORHEIGHTFRACTAL_H_

#include "Mfrc.h"


/*
 * How it works:
 * Mfrc* mfrc = new Mfrc();
 * AffectorHeightFractal* afhr = new AffectorHeightFractal(mfrc); //loads with default values
 * afhr->setSeed(0); ...
 * float height = afhr->getHeight(x, y);
 *
 */

class AffectorHeightFractal {
	byte* classStruct;

	//fractalID + 0x1C
	//var2 + 0x24
	// height + 0x20
	Mfrc* mfrc;

	byte* unknownStack;


public:

	AffectorHeightFractal(Mfrc* mfr) {
		mfrc = mfr;
		classStruct = (byte*) malloc(0x28);
		unknownStack = (byte*) malloc(0x30);

		memset(unknownStack, 0, 0x30);

		*(uint32*) (unknownStack + 24) = 0x16; // unknown



		ctor((int) classStruct);

		initializeValues();
	}

	~AffectorHeightFractal() {
		free (classStruct);
		free (unknownStack);
	}

	void setHeight(float value) {
		*(float*) (classStruct + 0x20) = value; // height
	}

	void setUnknownValue(int val) {
		*(uint32*) (classStruct + 0x24) = val; // var2
	}

	float getHeight(float x, float y, int i = 0, int j = 0) { // unknown i, j cant be > 0x16
		int table = (int)classStruct;

		int v9 = *(_DWORD *)(table + 28);
		if ( *(_DWORD *)(table + 24) != v9 )
		{
			*(_DWORD *)(table + 24) = v9;
			*(_DWORD *)(table + 20) = getMfrcPointer(v9);
		}

		return Mfrc::sub_13E7C00(*(_DWORD *)(table + 20), x, y, j, i) * *(float *)(table + 32); // * height
	}

	float trySubNoise(float x, float y, int i, int j) {
		int table = (int)classStruct;

		int v9 = *(_DWORD *)(table + 28);
		if ( *(_DWORD *)(table + 24) != v9 )
		{
			*(_DWORD *)(table + 24) = v9;
			*(_DWORD *)(table + 20) = getMfrcPointer(v9);
		}

		return Mfrc::sub_13E7C00(*(_DWORD *)(table + 20), x, y, j, i) * *(float *)(table + 32);
	}


private:

	void initializeValues() {
		*(uint32*) (classStruct + 0x1C) = 2; // fractal id
		*(uint32*) (classStruct + 0x24) = 0; // var2
		*(float*) (classStruct + 0x20) = 20.f; // height
	}

	int ctor(int table) {
	  int v2; // esi@1

	  v2 = table;
	  sub_B63440(table, 'AHFR', 2);
	  *(_DWORD *)(v2 + 5) = 0;
	  *(_DWORD *)(v2 + 7) = 0;
	  *(_DWORD *)(v2 + 9) = 0;
	  *(_DWORD *)(v2 + 6) = -1;
	  *(_DWORD *)(v2 + 8) = 0x3F800000; //1.0
	  *(_DWORD *)v2 = 0;// &AffectorHeightFractal___vftable_; no vftable for now
	  return v2;
	}

	int sub_B63440(int table, int a2, int a3) {
	  int v4 = table; // edx@1

	  sub_B62ED0(table, a2);
	  *(_DWORD *)(v4 + 16) = a3;
	  *(_DWORD *)v4 = 0;// TerrainGenerator__Affector___vftable_;
	  return v4;
	}

	int sub_B62ED0(int table, int a2)
	{
	  int result; // eax@1

	  result = table;
	  *(_DWORD *)(table + 4) = a2;
	  *(_BYTE *)(table + 8) = 1;
	  *(_DWORD *)(table + 12) = 0;
	  *(_DWORD *)table = 0;//TerrainGenerator__LayerItem___vftable_;
	  return result;
	}


	// crashes
	float tryProbableNoiseFunction(/*1.0f*/) {
		return probableNoiseFunction((int)classStruct, 0, 0, 1, 1, 1.0, (int)unknownStack);
	}


	// crashes use getHeight from above
	float probableNoiseFunction(int table, float a3, float a4, int a5, int a6, float a7, int a8) {
	  int v8; // esi@1
	  int v9; // eax@2
	  int v10; // edx@4
	  int v11; // ecx@4
	  int v12; // edi@4
	  long double v13; // fst6@4
	  long double v14; // fst7@4
	  int v15; // eax@4
	  long double v16; // fst6@5
	  long double v17; // fst7@5
	  long double v18; // fst7@6
	  long double v19; // fst6@7
	  char v20; // [sp-Ch] [bp-Ch]@4
	  float v21; // [sp+14h] [bp+14h]@4

	  v8 = table;
	  if ( a7 > 0.0 )
	  {
	    v9 = *(_DWORD *)(table + 28);
	    if ( *(_DWORD *)(table + 24) != v9 )
	    {
	      *(_DWORD *)(table + 24) = v9;
	      *(_DWORD *)(table + 20) = getMfrcPointer(v9);
	    }
	    //v20 = a2;
	    v12 = a6;
	    v14 = Mfrc::sub_13E7C00(*(_DWORD *)(v8 + 20), a3, a4, a5, a6) * *(float *)(v8 + 32);

	    v15 = *(_DWORD *)(a8 + 24);
	    v10 = *(_DWORD *)(v15 + 8);
	    v11 = a5 + a6 * *(_DWORD *)v15;
	    v13 = *(float *)(v10 + 4 * v11);
	    v21 = *(float *)(v10 + 4 * v11);
	    switch ( *(_DWORD *)(v8 + 36) )
	    {
	      case 1:
	        v16 = v14;
	        v17 = *(float *)(v10 + 4 * v11);
	        goto LABEL_11;
	      case 2:
	        v18 = v13 - v14 * a7;
	        break;
	      case 3:
	        v19 = v14 * v13;
	        v17 = *(float *)(v10 + 4 * v11);
	        goto LABEL_10;
	      case 4:
	       // Fatal("invalid operation", v20);
	        v18 = v21;
	        break;
	      default:
	        v19 = v14;
	        v17 = *(float *)(v10 + 4 * v11);
	LABEL_10:
	        v16 = v19 - v17;
	LABEL_11:
	        v18 = v17 + v16 * a7;
	        break;
	    }
	    *(float *)(*(_DWORD *)(*(_DWORD *)(a8 + 24) + 8) + 4 * (a5 + v12 * **(_DWORD **)(a8 + 24))) = v18;
	  }

	  return v18;
	}

	int getMfrcPointer(int table) {
		return (int)mfrc->getAsmStruct() + 8;//0x4C;
	  /*int v2; // eax@1

	  v2 = sub_B75DE0(a1);
	  return type_info::raw_name(v2);*/
	}



};


#endif /* AFFECTORHEIGHTFRACTAL_H_ */
