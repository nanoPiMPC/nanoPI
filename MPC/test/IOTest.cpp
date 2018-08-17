//
//  IOTest.cpp
//  
//
//  Created by Sourgroup on 2/28/18.
//

#include <stdio.h>
#include "Stage.hpp"
#define size 204800
int main(int argc,char ** argv)
{
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=2) return 0;
    int port;
    int MyID;
    MyID=atoi(argv[1]);
    port=atoi(argv[2]);
    
    IO.Setup(MyID,PartyNumber,port);
    unsigned char tmp[PartyNumber*size];
    unsigned char gather[PartyNumber*size];
    void *exsrc[PartyNumber],*exdst[PartyNumber];
    void *gadst[PartyNumber];
    
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(tmp[MyID*size]);
        exdst[i]=&(tmp[i*size]);
    }
    for(int i=0;i<1000;i++)
    {
        Exchange(&IO,exsrc,exdst,32000);
    }
    
}
