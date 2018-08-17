//
//  Wiremap.cpp
//  
//
//  Created by Sourgroup on 11/17/17.
//

#include "Wiremap.hpp"
wiremap Map;

void wiremap::Setup(int size)
{
    MapSize=size;
    array=(wire*)_mm_malloc(sizeof(wire)*(MapSize+2),16);
    available_Index=(Index*)malloc(sizeof(Index)*MapSize);
    AuthBitBed=(block *)_mm_malloc(sizeof(block)*(MapSize+2)*3*(PartyNumber-1),16);
    LabelBed=AuthBitBed+(MapSize+2)*2*(PartyNumber-1);
    next_Index_Index=MapSize-1;
    for(int i=0;i<MapSize;i++)
    {
        array[i].AuthBit=&(AuthBitBed[2*i*(PartyNumber-1)]);
        array[i].Label=&(LabelBed[i*(PartyNumber-1)]);
        available_Index[i]=MapSize-1-i;
    }
    Zero=MapSize;
    One=MapSize+1;
    for(int i=MapSize;i<MapSize+2;i++)
    {
        array[i].AuthBit=&(AuthBitBed[2*i*(PartyNumber-1)]);
        array[i].Label=&(LabelBed[i*(PartyNumber-1)]);
    }
    for(int i=0;i<2*(PartyNumber-1);i++)
    {
        array[MapSize].AuthBit[i]=_mm_set_epi32(0,0,0,0);
        array[MapSize+1].AuthBit[i]=_mm_set_epi32(0,0,0,0);
    }
    for(int i=0;i<(PartyNumber-1);i++)
    {
        array[MapSize].Label[i]=_mm_set_epi32(0,0,0,0);
        array[MapSize+1].Label[i]=_mm_set_epi32(0,0,0,0);
    }
}
void wiremap::ShutDown()
{
    _mm_free(array);
    free(available_Index);
    _mm_free(AuthBitBed);
}
Index wiremap::New()
{
    if(next_Index_Index<0) error("Out of memory");
    Index i=available_Index[next_Index_Index];
#ifdef debug
    if(array[i].Occupied){
        printf("%d\n ",i);
        error("Map error! 1");
    }
    array[i].Occupied=true;
#endif
    next_Index_Index--;
    return i;
}
Index wiremap:: Copy(Index src)
{
    Index dst=New();
    for(int i=0;i<2*(PartyNumber-1);i++)
    {
        array[dst].AuthBit[i]=array[src].AuthBit[i];
    }
    for(int i=0;i<(PartyNumber-1);i++)
        array[dst].Label[i]=array[src].Label[i];

    return dst;
}
wire* wiremap::Read(Index i)
{
#ifdef debug
    if(!(array[i].Occupied)) {
        error("Map error! 3");
    }
#endif
    return &(array[i]);
}
void wiremap::release(Index i)
{
#ifdef debug
    if(!(array[i].Occupied)) error("Map error! 4");
    array[i].Occupied=false;
    array[i].pre=0;
    array[i].eval=0;
#endif
    next_Index_Index++;
    available_Index[next_Index_Index]=i;
}

wire * READ(Index i)
{
    return Map.Read(i);
}
