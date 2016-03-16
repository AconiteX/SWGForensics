/*
 * Mfrc.cpp
 *
 *  Created on: 06/04/2010
 *      Author: TheAnswer
 */

#include "Mfrc.h"

float Mfrc::flt_19BB4C4 = 0;

int Mfrc::parseSeed(int table, int seed) {
	int result; // eax@1
	int v3; // esi@1

	result = seed;
	v3 = (int)table;
	if ( *(_DWORD *)table != seed || seed == 0) {
		*(_DWORD *)table = seed;
		sub_13E64D0((int)(table + 68), seed);
		result = sub_13E6B50(v3);
	}

	return result;
}

int Mfrc::initializeRandom(int a1) {
	int v1; // eax@1
	int v2; // edx@1
	int result; // eax@2

	/*byte_1947184 = 1;
	  registerRemove_(sub_B5A020, "Random::remove", 0, 0);*/
	v1 = (int) malloc(1296);
	v2 = v1;
	if ( v1 )
	{
		*(_DWORD *)v1 = -a1;
		*(_DWORD *)(v1 + 4) = 0;
		result = 0;
		memset((void *)(v2 + 8), 0, 0x508u);
		randomTable = (byte *)v2;

		//sub_13E64D0(v1, a1);
		sub_B59EF0(v2);
	}
	else
	{
		result = 0;
		randomTable = 0;
	}
	return result;
}


int Mfrc::sub_B75680(int table, int a2) { // CONTSTRUCTOR MFRC SHIT OMFG
	int v3; // esi@1

	v3 = table;
	*(_DWORD *)table = 0;
	*(_DWORD *)(table + 4) = a2;
	sub_13E6880(table + 8);
	return v3;
}

long double Mfrc::__FYL2X__(long double x, long double y) {
	long double result;

#if defined(_MSC_VER)
	// MSVC
	__asm
	{
		ffree ST(0);
		ffree ST(1);
		fld y;
		fld x;
		FYL2X;
		fst result;
	};
#else
	//gcc
	__asm __volatile__ (
			"fyl2x"
			: "=t" (result)
			  : "0" (x), "u" (y)
			    : "st(1)");
#endif


	return result;
}

long double Mfrc::sub_13E7C00(int table, float a2, float a3, int a4, int a5) {
	int v5; // ebx@1
	int v6; // esi@1
	int v7; // ebx@1
	int v8; // ecx@1
	int v9; // ebx@1
	char v10; // al@1
	long double v11; // fst7@2
	long double v12; // fst7@4
	long double result; // fst7@6
	int v14; // edi@8
	float v15; // ST04_4@10
	float v16; // ST00_4@10
	int v17; // edi@14
	float v18; // ST1C_4@16
	float v19; // ST04_4@16
	float v20; // ST00_4@16
	int v21; // edi@18
	float v22; // ST1C_4@20
	float v23; // ST04_4@20
	float v24; // ST00_4@20
	int v25; // edi@23
	long double v26; // fst7@24
	float v27; // ST04_4@24
	float v28; // ST00_4@24
	int v29; // edi@31
	long double v30; // fst7@32
	float v31; // ST04_4@32
	float v32; // ST00_4@32
	float v33; // [sp+18h] [bp-8h]@8
	float v34; // [sp+18h] [bp-8h]@14
	float v35; // [sp+1Ch] [bp-4h]@7
	float v36; // [sp+1Ch] [bp-4h]@9
	float v37; // [sp+1Ch] [bp-4h]@23
	float v38; // [sp+1Ch] [bp-4h]@31
	float v39; // [sp+28h] [bp+8h]@7
	float v40; // [sp+28h] [bp+8h]@48
	float v41; // [sp+2Ch] [bp+Ch]@7
	float v42; // [sp+2Ch] [bp+Ch]@9
	float v43; // [sp+2Ch] [bp+Ch]@15
	float v44; // [sp+2Ch] [bp+Ch]@19
	float v45; // [sp+2Ch] [bp+Ch]@23
	float v46; // [sp+2Ch] [bp+Ch]@31
	float v47; // [sp+30h] [bp+10h]@7
	float v48; // [sp+34h] [bp+14h]@7

	v6 = table;
	v7 = a5 * *(_DWORD *)(table + 9588);
	v8 = *(_DWORD *)(table + 9596);
	v9 = 16 * (a4 + v7);
	v10 = *(_BYTE *)(v9 + v8);
	v5 = v8 + v9;
	if ( v10 ) // checks for the last cached values?
	{
		v11 = *(float *)(v5 + 4);
		if ( v11 - 0.000009999999747378752 <= a2 )
		{
			if ( a2 <= v11 + 0.000009999999747378752 )
			{
				v12 = *(float *)(v5 + 8);
				if ( v12 - 0.000009999999747378752 <= a3 )
				{
					if ( a3 <= v12 + 0.000009999999747378752 )
						return *(float *)(v5 + 12);
				}
			}
		}
	}
	result = 0.0;
	v35 = 0.0;
	*(_BYTE *)v5 = 1;
	*(_DWORD *)(v5 + 4) = LODWORD(a2);
	*(_DWORD *)(v5 + 8) = LODWORD(a3);
	v39 = a2 * *(float *)(v6 + 4); // +4 = xfreq
	LODWORD(v48) = 1065353216; // 1.0
	LODWORD(v47) = 1065353216; // 1.0
	v41 = a3 * *(float *)(v6 + 8); // +8 = yfreq
	switch ( *(_DWORD *)(v6 + 56) ) // combination
	{
	case 0:
	case 1:
		v14 = *(_DWORD *)(v6 + 20); // octaves
		LODWORD(v33) = 0;
		if ( v14 > 0 )
		{
			v42 = v41 + *(float *)(v6 + 16); // + 16 = z.offset
			v36 = v39 + *(float *)(v6 + 12); // + 12 = x.offset
			do
			{
				v15 = v42 * v48;
				v16 = v36 * v48;
				--v14;
				v33 = sub_13E66F0((int)(v6 + 68), v16, v15) * v47 + v33;
				v48 = v48 * *(float *)(v6 + 24); // + 24 octaves param
				v47 = v47 * *(float *)(v6 + 28); // + 28 amplitud
			}
			while ( v14 );
		}
		if ( *(_BYTE *)(v6 + 52) ) // v6 + 52 initialized to 0
			v33 = sin(v33 + v39);
		result = (v33 * *(float *)(v6 + 32) + 1.0) * 0.5; //  v6 + 32 initialized to 1.0
		goto LABEL_40;
	case 2:
		v17 = *(_DWORD *)(v6 + 20); // octaves
		LODWORD(v34) = 0;
		if ( v17 > 0 )
		{
			v43 = v41 + *(float *)(v6 + 16); // + 16 = z.offset
			do
			{
				v19 = v43 * v48;
				v18 = v39 + *(float *)(v6 + 12); //  + 12 = x.offset
				v20 = v18 * v48;
				--v17;
				v34 = (1.0 - fabs(sub_13E66F0((int)(v6 + 68), v20, v19))) * v47 + v34;
				v48 = v48 * *(float *)(v6 + 24);  // + 24 octaves param
				v47 = v47 * *(float *)(v6 + 28); // + 28 amplitud
			}
			while ( v17 );
		}
		goto LABEL_37;
	case 3:
		v21 = *(_DWORD *)(v6 + 20); // // octaves
		LODWORD(v34) = 0;
		if ( v21 > 0 )
		{
			v44 = v41 + *(float *)(v6 + 16); // + 16 = z.offset
			do
			{
				v23 = v44 * v48;
				v22 = v39 + *(float *)(v6 + 12); //  + 12 = x.offset
				v24 = v22 * v48;
				--v21;
				v34 = fabs(sub_13E66F0((int)(v6 + 68), v24, v23)) * v47 + v34;
				v48 = v48 * *(float *)(v6 + 24); // + 24 octaves param
				v47 = v47 * *(float *)(v6 + 28);  // + 28 amplitud
			}
			while ( v21 );
		}
		goto LABEL_37;
	case 4:
		LODWORD(v34) = 0;
		if ( *(_DWORD *)(v6 + 20) > 0 ) // // octaves
		{
			v25 = *(_DWORD *)(v6 + 20); // // octaves
			v45 = v41 + *(float *)(v6 + 16); // + 16 = z.offset
			v37 = v39 + *(float *)(v6 + 12); //  + 12 = x.offset
			do
			{
				v27 = v45 * v48;
				v28 = v37 * v48;
				v26 = sub_13E66F0((int)(v6 + 68), v28, v27);
				if ( v26 >= 0.0 )
				{
					if ( v26 > 1.0 )
						v26 = 1.0;
				}
				else
				{
					v26 = 0.0;
				}
				--v25;
				v34 = (1.0 - v26) * v47 + v34;
				v48 = v48 * *(float *)(v6 + 24); // + 24 octaves param
				v47 = v47 * *(float *)(v6 + 28); // + 28 amplitud
			}
			while ( v25 );
		}
		goto LABEL_37;
	case 5:
		LODWORD(v34) = 0;
		if ( *(_DWORD *)(v6 + 20) > 0 ) // // octaves
		{
			v29 = *(_DWORD *)(v6 + 20);  // // octaves
			v46 = v41 + *(float *)(v6 + 16); //  + 16 = z.offset
			v38 = v39 + *(float *)(v6 + 12); //  + 12 = x.offset
			do
			{
				v31 = v46 * v48;
				v32 = v38 * v48;
				v30 = sub_13E66F0((int)(v6 + 68), v32, v31); //
				if ( v30 >= 0.0 )
				{
					if ( v30 > 1.0 )
						v30 = 1.0;
				}
				else
				{
					v30 = 0.0;
				}
				--v29;
				v34 = v30 * v47 + v34;
				v48 = v48 * *(float *)(v6 + 24); // v6 + 24 octaves param
				v47 = v47 * *(float *)(v6 + 28); // v6 + 28 amplitud
			}
			while ( v29 );
		}
		LABEL_37:
		if ( *(_BYTE *)(v6 + 52) )
			v34 = sin(v34 + v39);
		result = v34 * *(float *)(v6 + 32); // v6 + 32 initialized to 1.0
		LABEL_40:
		v35 = result;
		break;
	default:
		break;
	}
        if ( *(_BYTE *)(v6 + 36) ) // bias, v6 + 40 bias value
	{
                float var1 = __FYL2X__(0.5, 0.6931471805599453);
                float var2 = __FYL2X__(*(float *)(v6 + 40), 0.6931471805599453);
                float var3 = var2 / var1;
                result = pow((long double)(__FYL2X__(*(float *)(v6 + 40), 0.6931471805599453) / __FYL2X__(0.5, 0.6931471805599453)), (long double) v35);
		v35 = result;
	}
	if ( *(_BYTE *)(v6 + 44) ) // gain type
	{
		if ( result < 0.001 )
		{
			result = 0.0;
			*(float *)(v5 + 12) = 0.0;
			return result;
		}
		if ( result > 0.999 )
		{
			result = 1.0;
			*(float *)(v5 + 12) = 1.0;
			return result;
		}
		v40 = __FYL2X__(1.0 - *(float *)(v6 + 48), 0.6931471805599453) / flt_19BB4C4; // v6 + 48 gain value
		if ( result < 0.5 )
		{
			result = pow(v40, v35 + v35) * 0.5;
			*(float *)(v5 + 12) = result;
			return result;
		}
		result = 1.0 - pow((long double) v40, (long double) (1.0 - v35 + 1.0 - v35)) * 0.5;
	}
	*(float *)(v5 + 12) = result;
	return result;
}

double Mfrc::sub_13E66F0(int table, float a2, float a3)
{
	int v3; // ecx@1
	int v4; // esi@1
	double v5; // st7@1
	bool v6; // eax@3
	int v7; // ecx@5
	int v8; // ebx@5
	int v9; // edi@5
	double v10; // st6@5
	double v11; // st7@9
	bool v12; // eax@7
	int v13; // edx@9
	double v15; // st6@9
	int v16; // ecx@9
	int v17; // edi@9
	int v18; // eax@9
	int v19; // edx@9
        double sy; // st4@9
	double v21; // st3@9
	double v22; // st2@9
	int v23; // edi@9
	double v24; // st3@9
	int v25; // ecx@9
	int v26; // eax@9
	double v27; // st5@9
	float v28; // [sp+Ch] [bp+8h]@5

	v5 = a2 + 4096.0;
	v4 = table;
	v3 = (signed __int64)v5;
	v6 = v5 < 0.0 && v5 != (double)(signed int)(signed __int64)v5;
	v9 = (v3 - v6) & 0xFF;
	v8 = (((v3 - v6) & 0xFF) + 1) & 0xFF;
	v28 = v5 - (double)(v3 - v6);
	v10 = a3 + 4096.0;

	/*
	 * a2 + 4096
	 * int64 temp = (int64) a2 + 4096
	 * if (v5 < 0)
	 */


	v7 = (signed __int64)v10;
	v12 = v10 < 0.0 && v10 != (double)(signed int)(signed __int64)v10;
	v13 = *(_DWORD *)(v4 + 4 * v9 + 1296);
	v15 = v10 - (double)(v7 - v12);
	v16 = (v7 - v12) & 0xFF;
	v17 = v4 + 8 * *(_DWORD *)(v4 + 4 * (v13 + v16) + 1296) + 3352;
	v18 = (v16 + 1) & 0xFF;
	v19 = *(_DWORD *)(v4 + 4 * (v18 + v13) + 1296);
        sy = (3.0 - (v28 + v28)) * v28 * v28;
	v21 = v15 * *(float *)(v17 + 4);
	v22 = v28 * *(float *)v17;
        // what is v17?
	v23 = *(_DWORD *)(v4 + 4 * v8 + 1296);
	v24 = v21 + v22;
	v25 = v4 + 8 * *(_DWORD *)(v4 + 4 * (v23 + v16) + 1296) + 3352;
	v26 = v4 + 8 * *(_DWORD *)(v4 + 4 * (v18 + v23) + 1296) + 3352;
	v27 = (v15 - 1.0) * *(float *)(v4 + 8 * v19 + 3356) + v28 * *(float *)(v4 + 8 * v19 + 3352);
        v11 = v28 - 1.0;

        /*double result = (((v15 - 1.0) * *(float *)(v26 + 4) + v11 * *(float *)v26 - v27) * v20
                        + v27
                        - (v24
                                        + (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24) * v20))
                                        * (3.0 - (v15 + v15))
                                        * v15
                                        * v15
                                        + v24
                                        + (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24) * v20;
*/

        double par1 = ((v15 - 1.0) * *(float *)(v26 + 4) + v11 * *(float *)v26 - v27);
        double par2 = (v24 + (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24) * sy);


        double par3 = (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24);
        ///////////////*                  b1                            -  a1);

        double par4 = ( par1 * sy + v27 - par2);
                      /*        b       -  a */
        double sx = (3.0 - (v15 + v15)) * v15 * v15;

        double par6 = (par4 * sx);
                     //(b2-a2) * sx + a2 = v24

        double result = (par6 + v24) + sy * par3; // a + t * (b - a)
        //                     a1     + sy * (b1 - a1)
        // v20 = sy, (b - a) = par3, a = (par6 + v24)

	return result;
}



int Mfrc::sub_B59EC0(int table) {
	int v2; // esi@1

	v2 = table;
	*(_DWORD *)table = 1 - sub_B59EF0((int) randomTable);
	*((_DWORD *)v2 + 1) = 0;
	memset((char *)v2 + 8, 0, 0x508u);
	return v2;
}


int Mfrc::sub_13E6470(int table, int a2) {
	int v3; // esi@1

	v3 = (int)table;
	sub_B59EC0(table);
	sub_13E64D0(v3, a2);
	return v3;
}


int Mfrc::sub_13E6880(int table) {
	int v2; // esi@1
	int v3; // edi@1

	v2 = table;
	*(_DWORD *)table = 0;
	*(_DWORD *)(table + 4) = 0x3c23d70a; //9.999999776e-003
	*(_DWORD *)(table + 8) = 0x3c23d70a; //9.999999776e-003
	*(_DWORD *)(table + 12) = 0;
	*(_DWORD *)(table + 16) = 0;
	*(_DWORD *)(table + 20) = 2;
	*(_DWORD *)(table + 24) = 0x40800000; //4.
	*(_DWORD *)(table + 28) = 0x3F000000; //0.5
	*(_DWORD *)(table + 32) = 1065353216; //1.0
	*(_BYTE *)(table + 36) = 0;
	*(_DWORD *)(table + 40) = 0x3F000000;//0.5
	*(_BYTE *)(table + 44) = 0;
	*(_DWORD *)(table + 48) = 0x3F333333; //0.6999999881
	v3 = table + 68;
	*(_BYTE *)(table + 52) = 0;
	*(_DWORD *)(table + 56) = 0;
	*(_DWORD *)(table + 60) = 0;
	*(_DWORD *)(table + 64) = 0;
	sub_13E6470(v3, 0);
	*(_DWORD *)(v2 + 9588) = 0;
	*(_DWORD *)(v2 + 9592) = 0;
	*(_DWORD *)(v2 + 9596) = 0;
	sub_13E6DD0(v2);
	sub_13E6CB0(v2, 0);
	sub_13E64D0(v3, *(_DWORD *)v2);
	return v2;
}





int Mfrc::sub_13E64D0(int table, int seed) {
	int v2; // ebx@1
	int v3; // edi@1
	int v4; // esi@1
	int v5; // ebx@3
	int v6; // eax@4
	char v7; // zf@4
	int v8; // eax@5
	unsigned char v9; // sf@5
	unsigned char v10; // of@5
	long double v11; // fst5@5
	int v12; // eax@6
	int v13; // edi@7
	int v14; // ebx@8
	int v15; // eax@8
	int result; // eax@9
	signed int v18; // ecx@9
	int v19; // esi@9
	int v20; // edx@10
	int v21; // edi@10
	signed int v22; // [sp+10h] [bp-8h]@3
	int i; // [sp+14h] [bp-4h]@1
	int v24; // [sp+20h] [bp+8h]@1
	int v25; // [sp+20h] [bp+8h]@7

	v4 = table;
	v2 = table + 7464;
	*(_DWORD *)(table + 4) = 0;
	*(_DWORD *)table = -seed;
	v24 = 0;
	v3 = table + 3352;
	for ( i = table + 7464; ; v2 = i )
	{
		*(_DWORD *)(v2 - 6168) = v24;
		v22 = 2;
		*(float *)v2 = (long double)(sub_B59EF0(v4) % 512 - 256) * 0.00390625;
		v5 = v3;
		do
		{
			v6 = sub_B59EF0(v4) % 512;
			v5 += 4;
			v7 = v22-- == 1;
			*(float *)(v5 - 4) = (long double)(v6 - 256) * 0.00390625;
		}
		while ( !v7 );
		v8 = v24 + 1;
		v10 = __SETO__(v24 + 1, 256);
		v9 = v24++ - 255 < 0;
		i += 4;
		v11 = sqrt(*(float *)(v3 + 4) * *(float *)(v3 + 4) + *(float *)v3 * *(float *)v3);
		*(float *)v3 = 1.0 / v11 * *(float *)v3;
		*(float *)(v3 + 4) = 1.0 / v11 * *(float *)(v3 + 4);
		v3 = v5;
		if ( !(v9 ^ v10) )
			break;
	}
	v12 = v8 - 1;
	if ( v12 )
	{
		v13 = v4 + 4 * v12 + 1296;
		v25 = v12;
		do
		{
			v14 = *(_DWORD *)v13;
			v15 = sub_B59EF0(v4) % 256;
			*(_DWORD *)v13 = *(_DWORD *)(v4 + 4 * v15 + 1296);
			*(_DWORD *)(v4 + 4 * v15 + 1296) = v14;
			v13 -= 4;
		}
		while ( v25-- != 1 );
	}
	result = v4 + 3352;
	v19 = v4 + 2320;
	v18 = 258;
	do
	{
		*(_DWORD *)v19 = *(_DWORD *)(v19 - 1024);
		*(_DWORD *)(v19 + 6168) = *(_DWORD *)(v19 + 5144);
		v20 = *(_DWORD *)(result + 4);
		v21 = result + 2048;
		*(_DWORD *)(result + 2048) = *(_DWORD *)result;
		v19 += 4;
		result += 8;
		--v18;
		*(_DWORD *)(v21 + 4) = v20;
	}
	while ( v18 );
	return result;
}




int Mfrc::sub_B59EF0(int table) {
	long v1; // esi@1
	long v2; // eax@3
	long v3; // ebx@6
	signed long v4; // edi@6
	long v5; // ecx@7
	long v6; // ecx@13
	signed long long v8; // qax@15

	v1 = table;
	if ( *(_DWORD *)table <= 0 || !*(_DWORD *)(table + 4) )
	{
		v2 = -*(_DWORD *)table;
		if ( v2 >= 1 )
			*(_DWORD *)table = v2;
		else
			*(_DWORD *)table = 1;
		v4 = 329;
		v3 = table + 1324;
		do
		{
			int valueTo1 = *(_DWORD *)v1;
			int value2 = (16807 * valueTo1);
			int tempDiv = valueTo1 / 0x1F31D;
			int value3 = (0x7FFFFFFF * tempDiv);
			v5 = value2 - value3;
			*(_DWORD *)v1 = v5;
			if ( v5 < 0 )
				*(_DWORD *)v1 = v5 + 2147483647;
			if ( v4 < 322 )
				*(_DWORD *)v3 = *(_DWORD *)v1;
			--v4;
			v3 -= 4;
		}
		while ( v4 >= 0 );
		*(_DWORD *)(v1 + 4) = *(_DWORD *)(v1 + 8);
	}


	int valueTo1 = *(_DWORD *)v1;
	int value2 = (16807 * valueTo1);
	int tempDiv = valueTo1 / 0x1F31D;
	int value3 = (0x7FFFFFFF * tempDiv);

	v6 = value2 - value3; //16807 * *(_DWORD *)v1 - 2147483647 * *(_DWORD *)v1 / 127773;

	*(_DWORD *)v1 = v6;
	if ( v6 < 0 )
		*(_DWORD *)v1 = v6 + 2147483647;
	v8 = (signed long long)((long double)*(signed int *)(v1 + 4) / 6669205.0);
	HIDWORD(v8) = *(_DWORD *)v1;
        _DWORD * wtf = (_DWORD *)(v1 + 4 * v8 + 8);
        *(_DWORD *)(v1 + 4) = *wtf;
	*(_DWORD *)(v1 + 4 * v8 + 8) = HIDWORD(v8);
	return *(_DWORD *)(v1 + 4);
}

int Mfrc::sub_13E6DD0(int table) {
	int result; // eax@1
	long double v2; // fst5@2
	long double v3; // fst7@2

	result = *(_DWORD *)(table + 20);
	*(_DWORD *)(table + 32) = 0;
	if ( result > 0 )
	{
		v3 = 0.0;
		v2 = 1.0;
		do
		{
			--result;
			v3 = v3 + v2;
			v2 = v2 * *(float *)(table + 28);
		}
		while ( result );
		*(float *)(table + 32) = v3;
	}
	*(float *)(table + 32) = 1.0 / *(float *)(table + 32);
	return result;
}

int Mfrc::sub_13E6CB0(int table, int a2) { // call with table + 8
	int result; // eax@2

	*(int *)(table + 56) = a2;

	switch ( a2 )
	{
	case 0:
	case 1:
                *(int *)(table + 60) = (int) sub_13E6E50;
		*(int *)(table + 64) = (int) sub_13E7240;
		result = sub_13E6B50(table);
		break;
	case 2:
		*(int *)(table + 60) = (int) sub_13E6EE0;
		*(int *)(table + 64) = (int) sub_13E72E0;
		result = sub_13E6B50(table);
		break;
	case 3:
		*(int *)(table + 60) = (int) sub_13E6F60;
		*(int *)(table + 64) = (int) sub_13E7370;
		result = sub_13E6B50(table);
		break;
	case 4:
		*(int *)(table + 60) = (int) sub_13E6FE0;
		*(int *)(table + 64) = (int) sub_13E7400;
		result = sub_13E6B50(table);
		break;
	case 5:
		*(int *)(table + 60) = (int) sub_13E7090;
		*(int *)(table + 64) = (int) sub_13E74C0;
		result = sub_13E6B50(table);
		break;
	default:
		result = sub_13E6B50(table);
		break;
	}

	return result;
}

int Mfrc::sub_13E6B50(int table) {
	int result; // eax@1
	void *v2; // edi@1
	int i; // ecx@2
	int v4; // edi@2
	unsigned int v5; // edx@2

	result = (int) table;
	v2 = *(void **)(table + 9596);
	if ( v2 )
	{
		v5 = 16 * *(int *)(table + 9588) * *(int *)(table + 9592);
		result = 0;
		memset(v2, 0, 4 * (v5 >> 2));
		v4 = (int)((char *)v2 + 4 * (v5 >> 2));
		for ( i = v5 & 3; i; --i )
			*(byte *)v4++ = 0;
	}
	return result;
}


long double Mfrc::sub_13E6E50(float a1, byte* a2) {
	int v2; // edi@1
	float v3; // ST00_4@2
	float v5; // [sp+10h] [bp-Ch]@1
	float v6; // [sp+14h] [bp-8h]@1
	float v7; // [sp+18h] [bp-4h]@1

	v2 = *(int *)(a2 + 20);
	LODWORD(v6) = 1065353216;
	LODWORD(v5) = 1065353216;
	LODWORD(v7) = 0;

	if ( v2 > 0 ) {
		do {
			v3 = v6 * a1;
			--v2;
			v7 = sub_13E6650((byte *)(a2 + 68), v3) * v5 + v7;
			v6 = v6 * *(float *)(a2 + 24);
			v5 = v5 * *(float *)(a2 + 28);
		} while ( v2 );
	}

	if ( *(byte *)(a2 + 52) )
		v7 = sin(v7 + a1);

	return (v7 * *(float *)(a2 + 32) + 1.0) * 0.5;
}

long double Mfrc::sub_13E6650(byte* table, float a2) {
	int v2; // ecx@1
	void *v3; // esi@1
	long double v4; // fst7@1
	bool v5; // eax@3
	long double v7; // fst7@5
	int v8; // eax@5
	long double v9; // fst6@5
	signed int v10; // [sp+8h] [bp+8h]@1

	v4 = a2 + 4096.0;
	v3 = table;
	v2 = (signed long long)v4;
	v10 = (signed long long)v4;
	v5 = v4 < 0.0 && v4 != (long double)v10;
	v7 = v4 - (long double)(v2 - v5);
	v8 = (v2 - v5) & 0xFF;
	v9 = v7 * *((float *)v3 + *((int *)v3 + v8 + 324) + 1866);
	return ((v7 - 1.0) * *((float *)v3 + *((int *)v3 + ((v8 + 1) & 0xFF) + 324) + 1866) - v9)
	    				   * (3.0 - (v7 + v7))
	    				   * v7
	    				   * v7
	    				   + v9;
}

long double Mfrc::sub_13E7240(float a1, float a2, int a3) {
	int v3; // edi@1
	float v4; // ST04_4@2
	float v5; // ST00_4@2
	float v7; // [sp+14h] [bp-Ch]@1
	float v8; // [sp+18h] [bp-8h]@1
	float v9; // [sp+1Ch] [bp-4h]@1

	v3 = *(int *)(a3 + 20);
	LODWORD(v8) = 1065353216;
	LODWORD(v7) = 1065353216;
	LODWORD(v9) = 0;
	if ( v3 > 0 ) {
		do {
			v4 = v8 * a2;
			v5 = v8 * a1;
			--v3;
			v9 = sub_13E66F0((byte*) (a3 + 0x44), v5, v4) * v7 + v9;
			v8 = v8 * *(float *)(a3 + 24);
			v7 = v7 * *(float *)(a3 + 28);
		} while ( v3 );
	}

	if ( *(byte *)(a3 + 52) )
		v9 = sin(v9 + a1);

	return (v9 * *(float *)(a3 + 32) + 1.0) * 0.5;
}

long double Mfrc::sub_13E66F0(byte* table, float a2, float a3) {
	int v3; // ecx@1
	byte* v4; // esi@1
	long double v5; // fst7@1
	bool v6; // eax@3
	int v7; // ecx@5
	int v8; // ebx@5
	int v9; // edi@5
	long double v10; // fst6@5
	long double v11; // fst7@9
	bool v12; // eax@7
	int v13; // edx@9
	long double v15; // fst6@9
	int v16; // ecx@9
	int v17; // edi@9
	int v18; // eax@9
	int v19; // edx@9
	long double v20; // fst4@9
	long double v21; // fst3@9
	long double v22; // fst2@9
	int v23; // edi@9
	long double v24; // fst3@9
	int v25; // ecx@9
	int v26; // eax@9
	long double v27; // fst5@9
	float v28; // [sp+Ch] [bp+8h]@5

	v5 = a2 + 4096.0;
	v4 = table;
	v3 = (signed long long)v5;
	v6 = v5 < 0.0 && v5 != (long double)(signed int)(signed long long)v5;
	v9 = (v3 - v6) & 0xFF;
	v8 = (((v3 - v6) & 0xFF) + 1) & 0xFF;
	v28 = v5 - (long double)(v3 - v6);
	v10 = a3 + 4096.0;
	v7 = (signed long long)v10;
	v12 = v10 < 0.0 && v10 != (long double)(signed int)(signed long long)v10;
	v13 = *((int *)v4 + v9 + 324);
	v15 = v10 - (long double)(v7 - v12);
	v16 = (v7 - v12) & 0xFF;
	v17 = (int)(v4 + 8 * *((int *)v4 + v13 + v16 + 324) + 3352);
	v18 = (v16 + 1) & 0xFF;
	v19 = *((int *)v4 + v18 + v13 + 324);
	v20 = (3.0 - (v28 + v28)) * v28 * v28;
	v21 = v15 * *(float *)(v17 + 4);
	v22 = v28 * *(float *)v17;
	v23 = *((int *)v4 + v8 + 324);
	v24 = v21 + v22;
	v25 = (int)(v4 + 8 * *((int *)v4 + v23 + v16 + 324) + 3352);
	v26 = (int)(v4 + 8 * *((int *)v4 + v18 + v23 + 324) + 3352);
	v27 = (v15 - 1.0) * *((float *)v4 + 2 * v19 + 839) + v28 * *((float *)v4 + 2 * v19 + 838);
	v11 = v28 - 1.0;
	return (((v15 - 1.0) * *(float *)(v26 + 4) + v11 * *(float *)v26 - v27) * v20
			+ v27
			- (v24
					+ (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24) * v20))
					* (3.0 - (v15 + v15))
					* v15
					* v15
					+ v24
					+ (v15 * *(float *)(v25 + 4) + v11 * *(float *)v25 - v24) * v20;
}

long double Mfrc::sub_13E6EE0(float a1, int a2) {
	int v2; // edi@1
	float v3; // ST00_4@2
	long double v4; // fst7@3
	float v6; // [sp+10h] [bp-Ch]@1
	float v7; // [sp+14h] [bp-8h]@1
	float v8; // [sp+18h] [bp-4h]@1

	v2 = *(_DWORD *)(a2 + 20);
	LODWORD(v7) = 1065353216;
	LODWORD(v6) = 1065353216;
	LODWORD(v8) = 0;
	if ( v2 > 0 )
	{
		do
		{
			v3 = v7 * a1;
			--v2;
			v8 = (1.0 - fabs(sub_13E6650((byte *)(a2 + 68), v3))) * v6 + v8;
			v7 = v7 * *(float *)(a2 + 24);
			v6 = v6 * *(float *)(a2 + 28);
		}
		while ( v2 );
	}
	v4 = v8;
	if ( *(_BYTE *)(a2 + 52) )
		v4 = sin(v4 + a1);

	return v4 * *(float *)(a2 + 32);
}


long double Mfrc::sub_13E72E0(float a1, float a2, int a3) {
	int v3; // edi@1
	float v4; // ST04_4@2
	float v5; // ST00_4@2
	long double v6; // fst7@3
	float v8; // [sp+14h] [bp-Ch]@1
	float v9; // [sp+18h] [bp-8h]@1
	float v10; // [sp+1Ch] [bp-4h]@1

	v3 = *(_DWORD *)(a3 + 20);
	LODWORD(v10) = 1065353216;
	LODWORD(v8) = 1065353216;
	LODWORD(v9) = 0;
	if ( v3 > 0 ) {
		do {
			v4 = v10 * a2;
			v5 = v10 * a1;
			--v3;
			v9 = (1.0 - fabs(sub_13E66F0((byte *)(a3 + 68), v5, v4))) * v8 + v9;
			v10 = v10 * *(float *)(a3 + 24);
			v8 = v8 * *(float *)(a3 + 28);
		} while ( v3 );
	}
	v6 = v9;

	if ( *(_BYTE *)(a3 + 52) )
		v6 = sin(v6 + a1);
	return v6 * *(float *)(a3 + 32);
}


long double Mfrc::sub_13E6F60(float a1, int a2) {
	int v2; // edi@1
	float v3; // ST00_4@2
	long double v4; // fst7@3
	float v6; // [sp+10h] [bp-Ch]@1
	float v7; // [sp+14h] [bp-8h]@1
	float v8; // [sp+18h] [bp-4h]@1

	v2 = *(_DWORD *)(a2 + 20);
	LODWORD(v7) = 1065353216;
	LODWORD(v6) = 1065353216;
	LODWORD(v8) = 0;
	if ( v2 > 0 ) {
		do {
			v3 = v7 * a1;
			--v2;
			v8 = fabs(sub_13E6650((byte *)(a2 + 68), v3)) * v6 + v8;
			v7 = v7 * *(float *)(a2 + 24);
			v6 = v6 * *(float *)(a2 + 28);
		} while ( v2 );
	}
	v4 = v8;
	if ( *(_BYTE *)(a2 + 52) )
		v4 = sin(v4 + a1);
	return v4 * *(float *)(a2 + 32);
}

long double Mfrc::sub_13E7370(float a1, float a2, int a3) {
	int v3; // edi@1
	float v4; // ST04_4@2
	float v5; // ST00_4@2
	long double v6; // fst7@3
	float v8; // [sp+14h] [bp-Ch]@1
	float v9; // [sp+18h] [bp-8h]@1
	float v10; // [sp+1Ch] [bp-4h]@1

	v3 = *(_DWORD *)(a3 + 20);
	LODWORD(v10) = 1065353216;
	LODWORD(v8) = 1065353216;
	LODWORD(v9) = 0;
	if ( v3 > 0 )
	{
		do
		{
			v4 = v10 * a2;
			v5 = v10 * a1;
			--v3;
			v9 = fabs(sub_13E66F0((byte *)(a3 + 68), v5, v4)) * v8 + v9;
			v10 = v10 * *(float *)(a3 + 24);
			v8 = v8 * *(float *)(a3 + 28);
		}
		while ( v3 );
	}
	v6 = v9;
	if ( *(_BYTE *)(a3 + 52) )
		v6 = sin(v6 + a1);

	return v6 * *(float *)(a3 + 32);
}

long double Mfrc::sub_13E6FE0(float a1, int a2) {
	int v2; // edi@2
	long double v3; // fst7@3
	float v4; // ST00_4@3
	long double v5; // fst7@8
	float v7; // [sp+10h] [bp-Ch]@1
	float v8; // [sp+14h] [bp-8h]@1
	float v9; // [sp+18h] [bp-4h]@1

	LODWORD(v8) = 1065353216;
	LODWORD(v7) = 1065353216;
	LODWORD(v9) = 0;
	if ( *(_DWORD *)(a2 + 20) > 0 )
	{
		v2 = *(_DWORD *)(a2 + 20);
		do
		{
			v4 = v8 * a1;
			v3 = sub_13E6650((byte *)(a2 + 68), v4);
			if ( v3 >= 0.0 )
			{
				if ( v3 > 1.0 )
					v3 = 1.0;
			}
			else
			{
				v3 = 0.0;
			}
			--v2;
			v9 = (1.0 - v3) * v7 + v9;
			v8 = v8 * *(float *)(a2 + 24);
			v7 = v7 * *(float *)(a2 + 28);
		}
		while ( v2 );
	}
	v5 = v9;
	if ( *(_BYTE *)(a2 + 52) )
		v5 = sin(v5 + a1);
	return v5 * *(float *)(a2 + 32);
}

long double Mfrc::sub_13E7400(float a1, float a2, int a3) {
	int v3; // edi@2
	long double v4; // fst7@3
	float v5; // ST04_4@3
	float v6; // ST00_4@3
	long double v7; // fst7@8
	float v9; // [sp+14h] [bp-Ch]@1
	float v10; // [sp+18h] [bp-8h]@1
	float v11; // [sp+1Ch] [bp-4h]@1

	LODWORD(v11) = 1065353216;
	LODWORD(v9) = 1065353216;
	LODWORD(v10) = 0;
	if ( *(_DWORD *)(a3 + 20) > 0 )
	{
		v3 = *(_DWORD *)(a3 + 20);
		do
		{
			v5 = v11 * a2;
			v6 = v11 * a1;
			v4 = sub_13E66F0((byte *)(a3 + 68), v6, v5);
			if ( v4 >= 0.0 )
			{
				if ( v4 > 1.0 )
					v4 = 1.0;
			}
			else
			{
				v4 = 0.0;
			}
			--v3;
			v10 = (1.0 - v4) * v9 + v10;
			v11 = v11 * *(float *)(a3 + 24);
			v9 = v9 * *(float *)(a3 + 28);
		}
		while ( v3 );
	}
	v7 = v10;
	if ( *(_BYTE *)(a3 + 52) )
		v7 = sin(v7 + a1);
	return v7 * *(float *)(a3 + 32);
}

long double Mfrc::sub_13E7090(float a1, int a2) {
	int v2; // edi@2
	long double v3; // fst7@3
	float v4; // ST00_4@3
	long double v5; // fst7@8
	float v7; // [sp+10h] [bp-Ch]@1
	float v8; // [sp+14h] [bp-8h]@1
	float v9; // [sp+18h] [bp-4h]@1

	LODWORD(v8) = 1065353216;
	LODWORD(v7) = 1065353216;
	LODWORD(v9) = 0;
	if ( *(_DWORD *)(a2 + 20) > 0 )
	{
		v2 = *(_DWORD *)(a2 + 20);
		do
		{
			v4 = v8 * a1;
			v3 = sub_13E6650((byte *)(a2 + 68), v4);
			if ( v3 >= 0.0 )
			{
				if ( v3 > 1.0 )
					v3 = 1.0;
			}
			else
			{
				v3 = 0.0;
			}
			--v2;
			v9 = v3 * v7 + v9;
			v8 = v8 * *(float *)(a2 + 24);
			v7 = v7 * *(float *)(a2 + 28);
		}
		while ( v2 );
	}
	v5 = v9;
	if ( *(_BYTE *)(a2 + 52) )
		v5 = sin(v5 + a1);
	return v5 * *(float *)(a2 + 32);
}

long double Mfrc::sub_13E74C0(float a1, float a2, int a3)
{
	int v3; // edi@2
	long double v4; // fst7@3
	float v5; // ST04_4@3
	float v6; // ST00_4@3
	long double v7; // fst7@8
	float v9; // [sp+14h] [bp-Ch]@1
	float v10; // [sp+18h] [bp-8h]@1
	float v11; // [sp+1Ch] [bp-4h]@1

	LODWORD(v11) = 1065353216;
	LODWORD(v9) = 1065353216;
	LODWORD(v10) = 0;
	if ( *(_DWORD *)(a3 + 20) > 0 )
	{
		v3 = *(_DWORD *)(a3 + 20);
		do
		{
			v5 = v11 * a2;
			v6 = v11 * a1;
			v4 = sub_13E66F0((byte *)(a3 + 68), v6, v5);
			if ( v4 >= 0.0 )
			{
				if ( v4 > 1.0 )
					v4 = 1.0;
			}
			else
			{
				v4 = 0.0;
			}
			--v3;
			v10 = v4 * v9 + v10;
			v11 = v11 * *(float *)(a3 + 24);
			v9 = v9 * *(float *)(a3 + 28);
		}
		while ( v3 );
	}
	v7 = v10;
	if ( *(_BYTE *)(a3 + 52) )
		v7 = sin(v7 + a1);
	return v7 * *(float *)(a3 + 32);
}


