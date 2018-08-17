//
//  MOTE.hpp
//  
//
//  Created by Sourgroup on 12/13/17.
//

#ifndef MOTE_hpp
#define MOTE_hpp
#include "PRG.hpp"
#include "Network_IO.hpp"
#include "OTE.hpp"
class MOTSet
{
public:
    void Setup(int myid,block D,int size,block seed,Network *NIO);
    void MultiOT(block *dst,int n);
    void Refresh();
    int index;
    int MyID;
    int MOTBufferSize;
    Network *IO;
    block Delta;
    OTSet OTS[PartyNumber-1];
};
extern MOTSet MOT;
#endif /* OTE_hpp */
