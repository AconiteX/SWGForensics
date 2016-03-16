/*
 * FilterFractal.h
 *
 *  Created on: 06/04/2010
 *      Author: TheAnswer
 */

#ifndef FILTERFRACTAL_H_
#define FILTERFRACTAL_H_

#include "Mfrc.h"

class FilterFractal {
	byte* asmStruct;

	Mfrc* fractalParent;

public:
	FilterFractal(Mfrc* mfrc) {
		fractalParent = mfrc;
		initialize();
	}

	~FilterFractal() {
		free(asmStruct);
	}

	void initialize() {
		asmStruct = (byte*) malloc(0x34);

		ctor(asmStruct);

		setMfrcID(2);
		setVar2(0);
		setVar3(1);
		setVar4(0.532f);
		setVar5(0.596f);
		setVar6(1);
	}

	int setMfrcID(int a2) {
	  int result; // eax@1

	  result = a2;
	  *(_DWORD *)(asmStruct + 36) = a2;

	  return result;
	}

	int setVar2(int a2) {
	  int result; // eax@1

	  result = a2;
	  *(_DWORD *)(asmStruct + 20) = a2;

	  return result;
	}

	int setVar3(float var) {
		float temp;

		if (var >= 0.0) {
			if (var <= 1.0)
				temp = var;
			else
				temp = 1.0;
		} else
			temp = 0;

		*(float *)(asmStruct + 0x18) = temp;
	}

	int setVar4(float var) {
		*(float *)(asmStruct + 44) = var;

		return var;
	}

	int setVar5(float var) {
		*(float *)(asmStruct + 48) = var;

		return var;
	}

	float setVar6(float var) {
		*(float *)(asmStruct + 40) = var;

		return var;
	}

	void* ctor(void *object) {
	  void *v2; // esi@1

	  v2 = object;
	  FilterConstructor((int)v2, 'FFRA', 1);
	  *((_DWORD *)v2 + 7) = 0;
	  *((_DWORD *)v2 + 9) = 0;
	  *((_DWORD *)v2 + 11) = 0;
	  *((_DWORD *)v2 + 12) = 0;
	  *((_DWORD *)v2 + 8) = -1;
	  *((_DWORD *)v2 + 10) = 0x3F800000u;
	  *(_DWORD *)v2 = 0;//&FilterFractal___vftable_;
	  return v2;
	}

	int FilterConstructor(int object, int a2, int a3) {
	  int v4 = object; // edx@1

	  LayerItemConstructor(object, a2);
	  *(_DWORD *)(v4 + 20) = 0;
	  *(_DWORD *)(v4 + 24) = 0;
	  *(_DWORD *)(v4 + 16) = a3;
	  *(_DWORD *)v4 = 0;// TerrainGenerator__Filter___vftable_;
	  return v4;
	}

	int LayerItemConstructor(int object, int a2) {
	  int result; // eax@1

	  result = object;
	  *(_DWORD *)(object + 4) = a2;
	  *(_BYTE *)(object + 8) = 1;
	  *(_DWORD *)(object + 12) = 0;
	  *(_DWORD *)object = 0;//TerrainGenerator__LayerItem___vftable_;
	  return result;
	}

	long double processFilter(float x, float y, int i, int j) {
		return sub_B77BE0((int)asmStruct, x, y, i, j, 0);
	}

	long double sub_B77BE0(int object, float a2, float a3, int a4, int a5, int a6) {
		int v6; // eax@1
		int v7; // esi@1
		long double result; // fst7@5
		long double v9; // fst7@6
		float max; // [sp+10h] [bp+Ch]@3
		float var5; // [sp+14h] [bp+10h]@3
		float min; // [sp+18h] [bp+14h]@3
		float fractalResult; // [sp+1Ch] [bp+18h]@3

		v7 = object;
		v6 = *(_DWORD *)(object + 0x24);
		if ( *(_DWORD *)(object + 0x20) != v6 )
		{
			*(_DWORD *)(object + 0x20) = v6;
			*(_DWORD *)(object + 0x1C) = sub_B75B70(v6);
		}
		fractalResult = Mfrc::sub_13E7C00(*(_DWORD *)(v7 + 0x1C), a2, a3, a4, a5) * *(float *)(v7 + 0x28);
		LODWORD(min) = *(_DWORD *)(v7 + 0x2C);
		LODWORD(var5) = *(_DWORD *)(v7 + 0x30);
		LODWORD(max) = *(_DWORD *)(v7 + 0x18);
		if ( fractalResult > (long double)min && fractalResult < (long double)var5 )
		{
			v9 = (var5 - min) * max * 0.5;
			if ( min + v9 <= fractalResult ) {
				if ( var5 - v9 >= fractalResult )
					result = 1.0;
				else
					result = (var5 - fractalResult) / v9;
			} else {
				result = (fractalResult - min) / v9;
			}
		} else {
			result = 0.0;
		}

		return result;
	}

	int sub_B75B70(int id) {
		return (int)fractalParent->getAsmStruct() + 8;//0x4C;
	}

};

#endif /* FILTERFRACTAL_H_ */
