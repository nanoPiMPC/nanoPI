//
//  Wiremap.hpp
//  
//
//  Created by Sourgroup on 11/17/17.
//

#ifndef Wiremap_hpp
#define Wiremap_hpp

#include <stdio.h>
#include "util.hpp"
typedef int Index;
typedef struct{
#ifdef debug
    bool Occupied;
    unsigned char value;
    int pre;//preprocess visit;
    int eval;//evaluation visit;
#endif
    block *AuthBit;
    block *Label;
}wire;

class wiremap{
private:
    wire *array;
    int next_Index_Index;
    Index *available_Index;
    block *AuthBitBed,*LabelBed;
public:
    Index Zero,One;
    int MapSize;
    void Setup(int size);
    Index New();
    Index Copy(Index i);
    wire* Read(Index i);
    void release(Index i);
    void ShutDown();
};
extern wiremap Map;
wire * READ(Index i);
#endif /* Wiremap_hpp */

