/*
 * AffectorRoad.h
 *
 *  Created on: 08/01/2011
 *      Author: TheAnswer
 */

#ifndef AFFECTORROAD_H_
#define AFFECTORROAD_H_


/*
 *
 */

/*
 * signed int __thiscall sub_B7BAD0(int this)
{
  int v1; // ecx@1
  int v2; // ebx@1
  int v3; // eax@1
  int v4; // eax@2
  long double v5; // fst6@2
  long double v6; // fst7@2
  long double v7; // fst7@11
  int v8; // esi@13
  signed int result; // eax@15
  int v10; // ecx@16
  long double v11; // fst7@16
  int v12; // ecx@16
  long double v13; // fst6@16
  int v14; // ecx@18
  void *v15; // eax@22
  const void *v16; // edx@22
  int v17; // ST00_4@24
  float v18; // [sp+Ch] [bp-10h]@18
  void *v19; // [sp+10h] [bp-Ch]@22
  signed int i; // [sp+14h] [bp-8h]@15
  float v21; // [sp+18h] [bp-4h]@16
  int v22; // [sp+18h] [bp-4h]@20

  v2 = this;
  *(_DWORD *)(this + 0x44) = 2139095039;
  *(_DWORD *)(this + 0x48) = 2139095039;
  *(_DWORD *)(this + 0x4C) = -8388609;
  *(_DWORD *)(this + 0x50) = -8388609;
  v3 = *(_DWORD *)(this + 0x24);
  v1 = 0;
  if ( v3 > 0 )
  {
    do
    {
      v4 = *(_DWORD *)(v2 + 0x20);
      v6 = *(float *)(v4 + 8 * v1 + 4);
      v5 = *(float *)(v4 + 8 * v1);
      if ( v5 < *(float *)(v2 + 0x44) )
        *(float *)(v2 + 68) = *(float *)(v4 + 8 * v1);
      if ( v6 < *(float *)(v2 + 0x48) )
        *(float *)(v2 + 72) = v6;
      if ( v5 > *(float *)(v2 + 0x4C) )
        *(float *)(v2 + 76) = v5;
      if ( v6 > *(float *)(v2 + 0x50) )
        *(float *)(v2 + 80) = v6;
      ++v1;
    }
    while ( v1 < *(_DWORD *)(v2 + 0x24) );
  }
  v7 = *(float *)(v2 + 0x44) - *(float *)(v2 + 0x40);
  *(_DWORD *)(v2 + 0x30) = 0;
  *(_DWORD *)(v2 + 0x3C) = 0;
  *(float *)(v2 + 0x44) = v7;
  *(float *)(v2 + 0x48) = *(float *)(v2 + 0x48) - *(float *)(v2 + 0x40);
  *(float *)(v2 + 0x4C) = *(float *)(v2 + 0x40) + *(float *)(v2 + 0x4C);
  *(float *)(v2 + 0x50) = *(float *)(v2 + 0x40) + *(float *)(v2 + 0x50);
  if ( *(_DWORD *)(v2 + 0x30) == *(_DWORD *)(v2 + 0x28) )
    sub_B7C260((void *)(v2 + 0x28));
  *(_DWORD *)(*(_DWORD *)(v2 + 0x2C) + 4 * *(_DWORD *)(v2 + 0x30)++) = 0;
  v8 = v2 + 0x34;
  if ( *(_DWORD *)(v2 + 0x3C) == *(_DWORD *)(v2 + 0x34) )
    sub_B7C260((void *)(v2 + 0x34));
  *(_DWORD *)(*(_DWORD *)(v2 + 0x38) + 4 * *(_DWORD *)(v2 + 0x3C)++) = 0;
  result = 1;
  for ( i = 1; result < *(_DWORD *)(v2 + 0x24); i = result )
  {
    v10 = *(_DWORD *)(v2 + 0x20);
    v11 = *(float *)(v10 + 8 * result);
    v12 = v10 + 8 * result;
    v13 = *(float *)(v12 + 4) - *(float *)(v12 - 4);
    v21 = sqrt(v13 * v13 + (v11 - *(float *)(v12 - 8)) * (v11 - *(float *)(v12 - 8)));
    if ( *(_DWORD *)(v2 + 0x30) == *(_DWORD *)(v2 + 0x28) )
    {
      sub_B7C260((void *)(v2 + 0x28));
      result = i;
    }
    *(float *)(*(_DWORD *)(v2 + 0x2C) + 4 * *(_DWORD *)(v2 + 0x30)) = v21;
    ++*(_DWORD *)(v2 + 0x30);
    v14 = *(_DWORD *)v8;
    v18 = *(float *)(*(_DWORD *)(v2 + 0x38) + 4 * result - 4) + *(float *)(*(_DWORD *)(v2 + 0x2C) + 4 * result);
    if ( *(_DWORD *)(v8 + 8) == *(_DWORD *)v8 )
    {
      if ( v14 )
        v22 = 2 * v14;
      else
        v22 = 16;
      v15 = (void *)sub_AC15E0(4 * v22);
      v16 = *(const void **)(v8 + 4);
      v19 = v15;
      if ( v16 )
        memcpy(v15, v16, 4 * *(_DWORD *)v8);
      v8 = v2 + 0x34;
      v17 = *(_DWORD *)(v2 + 0x38);
      *(_DWORD *)(v2 + 0x34) = v22;
      sub_AC1660(v17);
      *(_DWORD *)(v2 + 0x38) = v19;
      result = i;
    }
    *(float *)(*(_DWORD *)(v8 + 4) + 4 * *(_DWORD *)(v8 + 8)++) = v18;
    ++result;
  }
  return result;
}
 *
 */

#endif /* AFFECTORROAD_H_ */
