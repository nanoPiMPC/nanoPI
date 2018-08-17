//
//  MOTE.cpp
//
//
//  Created by Sourgroup on 12/13/17.
//
#include "MOTE.hpp"
MOTSet MOT;
void MOTSet::Setup(int myid,block D,int size,block seed,Network *NIO)
{
    IO=NIO;
    MyID=myid;
    MOTBufferSize=size;
    Delta=D;
    for(int i=0;i<PartyNumber;i++)
    {
        for(int j=i+1;j<PartyNumber;j++)
        {
            if(i==MyID)
            {
                OTS[index].Setup(i,j,D,size,seed,IO);
                index++;
            }
            if(j==MyID)
            {
                OTS[index].Setup(j,i,D,size,seed,IO);
                index++;
            }
        }
    }
    Refresh();
    index=40;
    //a proof
}
void MOTSet::Refresh()
{

    void *exsrc[PartyNumber],*exdst[PartyNumber];
    void *exsrc1[PartyNumber],*exdst1[PartyNumber];
    
    for(int i=0;i<PartyNumber-1;i++)
    {
        OTS[i].OTExtension1(OTS[i].OTBuffer);
    }
    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&(OTS[i].OTEtemp[168*(OTS[i].size)*2]);
            exdst[i]=&(OTS[i].OTEtemp[168*(OTS[i].size)*3]);
        }
        if(i>MyID)
        {
            exsrc[i]=&(OTS[i-1].OTEtemp[168*(OTS[i-1].size)*2]);
            exdst[i]=&(OTS[i-1].OTEtemp[168*(OTS[i-1].size)*3]);
        }
    }
    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc1[i]=OTS[i].MatrixI;
            exdst1[i]=OTS[i].MatrixR;
        }
        if(i>MyID)
        {
            exsrc1[i]=OTS[i-1].MatrixI;
            exdst1[i]=OTS[i-1].MatrixR;
        }
    }
    DoublExchange(IO,exdst,exdst1,exsrc,exsrc1,16*168*(OTS[0].size),168*16);
    for(int i=0;i<PartyNumber-1;i++)
    {
        
        OTS[i].OTExtension2(OTS[i].OTBuffer);
#ifndef WRKSimulator
        OTS[i].DeltaConsistencyCheck1();
#endif
    }
#ifndef WRKSimulator
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&OTS[i].tmp[0];
            exdst[i]=&OTS[i].tmp[1];
        }
        if(i>MyID)
        {
            exsrc[i]=&OTS[i-1].tmp[0];
            exdst[i]=&OTS[i-1].tmp[1];
        }
    }
    Exchange(IO,exdst,exsrc,16);
    
    for(int i=0;i<PartyNumber-1;i++)
        OTS[i].DeltaConsistencyCheck2();
    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&(OTS[i].hash[SHA256_DIGEST_LENGTH]);
            exdst[i]=&(OTS[i].hash[SHA256_DIGEST_LENGTH*2]);
        }
        if(i>MyID)
        {
            exsrc[i]=&(OTS[i-1].hash[SHA256_DIGEST_LENGTH]);
            exdst[i]=&(OTS[i-1].hash[SHA256_DIGEST_LENGTH*2]);
        }
    }
    Exchange(IO,exdst,exsrc,SHA256_DIGEST_LENGTH);
#endif
    for(int i=0;i<PartyNumber-1;i++)
    {
        #ifndef WRKSimulator
        OTS[i].DeltaConsistencyCheck3();
        #endif
        OTS[i].OTExtension3(OTS[i].OTBuffer);
        OTS[i].ConsistencyCheck1();
    }
    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&OTS[i].seed;
            exdst[i]=&OTS[i].seedR;
        }
        if(i>MyID)
        {
            exsrc[i]=&OTS[i-1].seed;
            exdst[i]=&OTS[i-1].seedR;
        }
    }
    Exchange(IO,exdst,exsrc,16);
    for(int i=0;i<PartyNumber-1;i++)
    {
        OTS[i].ConsistencyCheck2();
    }
    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&(OTS[i].x);
            exdst[i]=&(OTS[i].X);
        }
        if(i>MyID)
        {
            exsrc[i]=&(OTS[i].x);
            exdst[i]=&(OTS[i].X);
        }
    }
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc1[i]=(OTS[i].t);
            exdst1[i]=(OTS[i].tt);
        }
        if(i>MyID)
        {
            exsrc1[i]=(OTS[i-1].t);
            exdst1[i]=(OTS[i-1].tt);
        }
    }
    DoublExchange(IO,exdst,exdst1,exsrc,exsrc1,16,32);

    for(int i=0;i<PartyNumber-1;i++)
    {
        
        OTS[i].ConsistencyCheck3();
        OTS[i].OTExtension4(OTS[i].OTBuffer);
    }
    index=0;
}
void MOTSet::MultiOT(block *dst,int n)
{
    if(n+index<MOTBufferSize)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<PartyNumber-1;j++)
            {
                dst[i*2*(PartyNumber-1)+2*j]=OTS[j].OTBuffer[index+MOTBufferSize+i];
                dst[i*2*(PartyNumber-1)+2*j+1]=OTS[j].OTBuffer[index+i];
            }
        }
        index+=n;
    }
    else{
        int count=MOTBufferSize-index;
        for(int i=0;i<count;i++)
        {
            for(int j=0;j<PartyNumber-1;j++)
            {
                dst[i*2*(PartyNumber-1)+2*j]=OTS[j].OTBuffer[index+MOTBufferSize+i];
                dst[i*2*(PartyNumber-1)+2*j+1]=OTS[j].OTBuffer[index+i];
            }
        }
        Refresh();
        MultiOT(dst+2*(PartyNumber-1)*count,n-count);
    }
}

