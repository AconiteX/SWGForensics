/*
 * Mfrc.h
 *
 *  Created on: 03/04/2010
 *      Author: TheAnswer
 */

#ifndef MFRC_H_
#define MFRC_H_

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER)
#include <windows.h>
#endif


//#define __SETO__(x, y) int(x - y) < 0;							// Generate overflow flags for (x-y)
#define __SETO__(x, y)   0							// Generate overflow flags for (x-y)
#define HIDWORD(x)  (*((int*)&(x)+1))
#define LODWORD(x)  (*((int*)&(x)))  // low dword

//MSVC
#if defined(_MSC_VER)
typedef DWORD _DWORD;
typedef BYTE _BYTE;
typedef DWORD uint32;
#else
//GCC
typedef unsigned char byte;
typedef unsigned long _DWORD;
typedef byte _BYTE;
typedef unsigned int uint32;
#endif
//typedef long long __int64;



class Mfrc {
	//int seed;

	byte* asmStruct;

	byte* unknownStruct;

	byte* mfrcOffset;



	/*
	 * all following offsets relative to asmStruct + 8
	 * +24h -> bias
	 * +28h -> bias value
	 * +2c -> gain type
	 * +30h -> gain value
	 * +14h -> octaves
	 * +18h -> octaves param
	 * +1Ch -> amplitud, needs a sub_13E6DD0(asmStruct + 8) call after setting the param
	 * +4h -> x freq (floaT)
	 * +8h -> y freq (float)
	 * +0c -> x offset (float)
	 * +10h -> z offset (float)
	 * +38h -> use combination, calls sub_13E6CB0((asmStruct + 8), combination)
	 */

	byte* randomTable;

public:
	static float flt_19BB4C4;

	Mfrc() {
		//seed = 0;

		randomTable = NULL;
		initializeRandom(time(NULL));
		asmStruct = (byte*) malloc(0x2588);
		mfrcOffset = asmStruct + 8;
		//memset(asmStruct, 0, 0x2588);

		unknownStruct = (byte*) malloc(0x1E40);
		memset(unknownStruct, 0, 0x1E40);

		uint32 wtf = 0x0BF317218;
		flt_19BB4C4 = *(float*) (&wtf) ;

		sub_B75680((int)asmStruct, 1); // wtf is 2?

		initializeValues();
	}

	~Mfrc() {
		free(asmStruct);
		free(randomTable);
		free(unknownStruct);
	}

	void setSeed(int seed) {
		parseSeed((int)mfrcOffset, seed);
	}

	void setBias(int bias) {
		*(uint32*) (mfrcOffset + 0x24) = bias; // bias
	}

	void setBiasValue(float value) {
		*(float*) (mfrcOffset + 0x28) = value; // bias value
	}

	void setGainType(int type) {
		*(uint32*) (mfrcOffset + 0x2C) = type; // gain type
	}

	void setGainValue(float val) {
		*(float*) (mfrcOffset + 0x30) = val; // gain value
	}

	void setOctaves(int octaves) {
		*(uint32*) (mfrcOffset + 0x14) = octaves; // octaves
	}

	void setOctavesParam(float param) {
		*(float*) (mfrcOffset + 0x18) = param; // octaves param
	}

	void setAmplitud(float ampl) {
		*(float*) (mfrcOffset + 0x1C) = ampl; // amplitud
		sub_13E6DD0((int)mfrcOffset); // needed call after setting amplitud
	}

	void setXFreq(float xfreq) {
		*(float*) (mfrcOffset + 0x4) = xfreq; // x.freq
	}

	void setYFreq(float yfreq) {
		*(float*) (mfrcOffset + 0x8) = yfreq; // y.freq
	}

	void setZOffset(float offset) {
		*(float*) (mfrcOffset + 0x10) = offset; // z.offset
	}

	void setXOffset(float offset) {
		*(float*) (mfrcOffset + 0x0C) = offset; // x.offset
	}

	void setCombination(int comb) {
		*(uint32*) (mfrcOffset + 0x38) = comb; // combination
		sub_13E6CB0((int)mfrcOffset, comb);
	}

	byte* getAsmStruct() {
		return asmStruct;
	}

private:

	void initializeValues() {
                parseSeed((int)mfrcOffset, 0);
                //parseSeed((int)mfrcOffset, 0);
                *(uint32*) (mfrcOffset + 0x24) = 0;//0; // bias
                *(float*) (mfrcOffset + 0x28) = 0.1; // bias value
		*(uint32*) (mfrcOffset + 0x2C) = 0; // gain type
		*(float*) (mfrcOffset + 0x30) = 0.7; // gain value
                *(uint32*) (mfrcOffset + 0x14) = 2; // octaves
		*(float*) (mfrcOffset + 0x18) = 4; // octaves param
		*(float*) (mfrcOffset + 0x1C) = 0.5; // amplitud
		sub_13E6DD0((int)mfrcOffset); // needed call after setting amplitud
                *(float*) (mfrcOffset + 0x4) = 0.01; // x.freq
                *(float*) (mfrcOffset + 0x8) = 0.01; // y.freq
		*(float*) (mfrcOffset + 0x10) = 0; // z.offset
		*(float*) (mfrcOffset + 0x0C) = 0; // x.offset
		*(uint32*) (mfrcOffset + 0x38) = 0; // combination
		sub_13E6CB0((int)mfrcOffset, 0);

		*(uint32*) (mfrcOffset + 9596) = (int) unknownStruct; // ?
		*(uint32*) (mfrcOffset + 9592) = 0x16; // ?
		*(uint32*) (mfrcOffset + 9588) = 0x16; // ?
		sub_13E6B50((int) mfrcOffset);


	}

	/*byte* trySeed() {
		return (byte*) parseSeed((int)asmStruct + 8, 6584);
	}*/

	int parseSeed(int table, int seed);

	int initializeRandom(int a1);

	int sub_B75680(int table, int a2);

	static long double __FYL2X__(long double x, long double y);

public:
	static long double sub_13E7C00(int table, float a2, float a3, int a4, int a5);
        static double sub_13E66F0(int table, float a2, float a3);


	int sub_B59EC0(int table);
	int sub_13E6470(int table, int a2);

	int sub_13E6880(int table);
	int sub_13E64D0(int table, int seed);
	int sub_B59EF0(int table);
	int sub_13E6DD0(int table);
	int sub_13E6CB0(int table, int a2);
	static int sub_13E6B50(int table);
	static long double  sub_13E6E50(float a1, byte* a2);
	static long double sub_13E6650(byte* table, float a2);
	static long double sub_13E7240(float a1, float a2, int a3);
	static long double sub_13E66F0(byte* table, float a2, float a3);
	static long double sub_13E6EE0(float a1, int a2);
	static long double sub_13E72E0(float a1, float a2, int a3);
	static long double sub_13E6F60(float a1, int a2);
	static long double sub_13E7370(float a1, float a2, int a3);
	static long double sub_13E6FE0(float a1, int a2);
	static long double sub_13E7400(float a1, float a2, int a3);
	static long double sub_13E7090(float a1, int a2);
	static long double sub_13E74C0(float a1, float a2, int a3);
};


#endif /* MFRC_H_ */
