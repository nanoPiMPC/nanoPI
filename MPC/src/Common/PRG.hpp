//
//  PRG.h
//  
//
//  Created by Sourgroup on 9/9/17.
//
//

#ifndef PRG_h
#define PRG_h
#include "aes.h"
#include <wmmintrin.h>
#include <emmintrin.h>
#include <xmmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
static inline void PRG(block *dst,unsigned int n, AES_KEY *seed,uint64_t *count)
{
    uint64_t i;
    block *tmp;
    tmp=(block *)_mm_malloc(sizeof(block)*n,32);
    
    for(i=*count;i<n+*count;i++)
    {
        dst[i-*count]=_mm_set_epi64x(i,i);
    }
    *count+=n;
    memcpy(tmp,dst,n*16);
    AES_ecb_encrypt_blks(dst,n,seed);
    for(i=0;i<n;i++)
        dst[i]=_mm_xor_si128(dst[i],tmp[i]);
    _mm_free(tmp);
}


#endif /* PRG_h */
