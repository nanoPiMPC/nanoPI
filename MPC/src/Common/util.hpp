//
//  util.hpp
//  
//
//  Created by Sourgroup on 10/24/17.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <stdlib.h>
#include "PRG.hpp"
#include <chrono>
using std::chrono::time_point;
using std::chrono::high_resolution_clock;

inline void error(const char *msg)
{
    printf("%s\n",msg);
    exit(0);
}

inline time_point<high_resolution_clock> clock_start() {
    return high_resolution_clock::now();
}

inline double time_from(const time_point<high_resolution_clock>& s) {
    return std::chrono::duration_cast<std::chrono::microseconds>(high_resolution_clock::now() - s).count();
}

inline void print128_num(__m128i var)
{
    uint8_t *val = (uint8_t*) &var;
    int i;
    for(i=15;i>=0;i--)
        printf("%02x ",val[i]);
    printf("\n");
}
inline void printM(block *a)
{
    for(int i=0;i<128;i++)
    {
        print128_num(a[i]);
    }printf("\n");
}
inline unsigned char extract_bit(block l)
{
    return (_mm_extract_epi8(l,0)&1);
}
inline void Transpose(block *dst,block *src)
{
    block r[4][128];
    for(int i=0;i<64;i++)
        r[0][i]=_mm_unpackhi_epi8(src[2*i+1],src[2*i]);
    for(int i=0;i<64;i++)
        r[0][64+i]=_mm_unpacklo_epi8(src[2*i+1],src[2*i]);
    for(int j=0;j<2;j++)
    {
        for(int i=0;i<32;i++)
            r[1][i+j*64]=_mm_unpackhi_epi16(r[0][2*i+1+j*64],r[0][2*i+j*64]);
        for(int i=0;i<32;i++)
            r[1][32+i+j*64]=_mm_unpacklo_epi16(r[0][2*i+1+j*64],r[0][2*i+j*64]);
    }
    
    for(int j=0;j<4;j++)
    {
        for(int i=0;i<16;i++)
            r[2][i+j*32]=_mm_unpackhi_epi32(r[1][2*i+1+j*32],r[1][2*i+j*32]);
        for(int i=0;i<16;i++)
            r[2][16+i+j*32]=_mm_unpacklo_epi32(r[1][2*i+1+j*32],r[1][2*i+j*32]);
    }

    for(int j=0;j<8;j++)
    {
        for(int i=0;i<8;i++)
            r[3][i+j*16]=_mm_unpackhi_epi64(r[2][2*i+1+j*16],r[2][2*i+j*16]);
        for(int i=0;i<8;i++)
            r[3][8+i+j*16]=_mm_unpacklo_epi64(r[2][2*i+1+j*16],r[2][2*i+j*16]);
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
        {
            dst[127-(j*8+i)]=_mm_set_epi16(_mm_movemask_epi8(r[3][j*8]),_mm_movemask_epi8(r[3][j*8+1]),_mm_movemask_epi8(r[3][j*8+2]),_mm_movemask_epi8(r[3][j*8+3]),_mm_movemask_epi8(r[3][j*8+4]),_mm_movemask_epi8(r[3][j*8+5]),_mm_movemask_epi8(r[3][j*8+6]),_mm_movemask_epi8(r[3][j*8+7]));
        }
        for(int j=0;j<128;j++)
        {
            r[3][j]=_mm_slli_epi16(r[3][j],1);
        }
    }
}
const block signpad=_mm_set_epi32(0,0,0,1);
inline void LSTranspose(block *dst, block *ls)
{
    unsigned char *p=(unsigned char*)ls;
    for(int i=0;i<16;i++)
    {
        dst[i*8]=_mm_set_epi32(0,0,0,p[i]);
    }
    for(int i=0;i<16;i++)
    {
        for(int j=1;j<8;j++)
            dst[i*8+j]=_mm_srli_epi16(dst[i*8+j-1],1);
    }
    for(int i=0;i<128;i++)
        dst[i]=_mm_and_si128(dst[i],signpad);
}
inline void LSCompress(block *dst, block *src)
{
    block mtmp[8];
    block tmp[16];
    unsigned char *p[16];
    for(int i=0;i<16;i++)
        p[i]=(unsigned char *)&(tmp[i]);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
            tmp[j]=_mm_slli_epi16(src[i*16+j],7);
        mtmp[i]=_mm_set_epi8(*p[15],*p[14],*p[13],*p[12],*p[11],*p[10],*p[9],*p[8],*p[7],*p[6],*p[5],*p[4],*p[3],*p[2],*p[1],*p[0]);
    }
    dst[0]=_mm_set_epi16(_mm_movemask_epi8(mtmp[7]),_mm_movemask_epi8(mtmp[6]),_mm_movemask_epi8(mtmp[5]),_mm_movemask_epi8(mtmp[4]),_mm_movemask_epi8(mtmp[3]),_mm_movemask_epi8(mtmp[2]),_mm_movemask_epi8(mtmp[1]),_mm_movemask_epi8(mtmp[0]));
}

inline void RSCompress(block *dst, block *src)
{
    block mtmp[8];
    block tmp[16];
    unsigned char *p[16];
    for(int i=0;i<16;i++)
        p[i]=(unsigned char *)&(tmp[i]);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
            tmp[j]=_mm_slli_epi16(src[i*16+j],7);
        mtmp[i]=_mm_set_epi8(*p[0],*p[1],*p[2],*p[3],*p[4],*p[5],*p[6],*p[7],*p[8],*p[9],*p[10],*p[11],*p[12],*p[13],*p[14],*p[15]);
    }
    dst[0]=_mm_set_epi16(_mm_movemask_epi8(mtmp[0]),_mm_movemask_epi8(mtmp[1]),_mm_movemask_epi8(mtmp[2]),_mm_movemask_epi8(mtmp[3]),_mm_movemask_epi8(mtmp[4]),_mm_movemask_epi8(mtmp[5]),_mm_movemask_epi8(mtmp[6]),_mm_movemask_epi8(mtmp[7]));
}

inline void LSCompressTuple(block *dst, block *src,int d)
{
    block mtmp[8];
    block tmp[16];
    unsigned char *p[16];
    for(int i=0;i<16;i++)
        p[i]=(unsigned char *)&(tmp[i]);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
            tmp[j]=_mm_slli_epi16(src[(i*16+j)*6+d],7);
        mtmp[i]=_mm_set_epi8(*p[15],*p[14],*p[13],*p[12],*p[11],*p[10],*p[9],*p[8],*p[7],*p[6],*p[5],*p[4],*p[3],*p[2],*p[1],*p[0]);
    }
    dst[0]=_mm_set_epi16(_mm_movemask_epi8(mtmp[7]),_mm_movemask_epi8(mtmp[6]),_mm_movemask_epi8(mtmp[5]),_mm_movemask_epi8(mtmp[4]),_mm_movemask_epi8(mtmp[3]),_mm_movemask_epi8(mtmp[2]),_mm_movemask_epi8(mtmp[1]),_mm_movemask_epi8(mtmp[0]));
}
inline void LSCompressTupleAnd(block *dst, block *src)
{
    block mtmp[8];
    block tmp[16];
    unsigned char *p[16];
    for(int i=0;i<16;i++)
        p[i]=(unsigned char *)&(tmp[i]);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<16;j++)
            tmp[j]=_mm_slli_epi16(_mm_and_si128(src[(i*16+j)*6],src[(i*16+j)*6+2]),7);
        mtmp[i]=_mm_set_epi8(*p[15],*p[14],*p[13],*p[12],*p[11],*p[10],*p[9],*p[8],*p[7],*p[6],*p[5],*p[4],*p[3],*p[2],*p[1],*p[0]);
    }
    dst[0]=_mm_set_epi16(_mm_movemask_epi8(mtmp[7]),_mm_movemask_epi8(mtmp[6]),_mm_movemask_epi8(mtmp[5]),_mm_movemask_epi8(mtmp[4]),_mm_movemask_epi8(mtmp[3]),_mm_movemask_epi8(mtmp[2]),_mm_movemask_epi8(mtmp[1]),_mm_movemask_epi8(mtmp[0]));
}
inline void print(__m128i var)
{
    uint16_t *val = (uint16_t*) &var;
    printf("%d %04x %04x %04x %04x %04x %04x %04x %04x \n",_mm_extract_epi8(var,0)%2,
           val[7], val[6], val[5], val[4], val[3], val[2],
           val[1], val[0]);
}
inline void printBit(__m128i *var)
{

    printf("Bit:\n");
    print(*var);
    print(*(var+1));
    printf("-------\n");
//    print(_mm_xor_si128(*(var+1),P.Delta));
}

inline void printHash(__m128i *var)
{
    uint16_t *val = (uint16_t*) &var[0];
    printf("Hash:\n%04x %04x %04x %04x %04x %04x %04x %04x \n",
           val[7], val[6], val[5], val[4], val[3], val[2],
           val[1], val[0]);
    val = (uint16_t*) &var[1];
    printf("%04x %04x %04x %04x %04x %04x %04x %04x \n\n",
           val[7], val[6], val[5], val[4], val[3], val[2],
           val[1], val[0]);
    
}

inline void printTuple(__m128i *var)
{
    printf("Tuple:\n");
    printBit(var);
    printBit(var+2);
    printBit(var+4);
    printf("==========\n");
}
inline void mul128(__m128i a, __m128i b, __m128i *res1, __m128i *res2)
{
    __m128i tmp3, tmp4, tmp5, tmp6;
    
    tmp3 = _mm_clmulepi64_si128(a, b, 0x00);
    tmp4 = _mm_clmulepi64_si128(a, b, 0x10);
    tmp5 = _mm_clmulepi64_si128(a, b, 0x01);
    tmp6 = _mm_clmulepi64_si128(a, b, 0x11);
    
    tmp4 = _mm_xor_si128(tmp4, tmp5);
    tmp5 = _mm_slli_si128(tmp4, 8);
    tmp4 = _mm_srli_si128(tmp4, 8);
    tmp3 = _mm_xor_si128(tmp3, tmp5);
    tmp6 = _mm_xor_si128(tmp6, tmp4);
    // initial mul now in tmp3, tmp6
    *res1 = tmp3;
    *res2 = tmp6;
}
#endif /* util_hpp */
