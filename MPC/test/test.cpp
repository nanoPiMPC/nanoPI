//
//  OTTest.cpp
//
//
//  Created by Sourgroup on 1/8/18.
//

#include <stdio.h>
#include "Stage.hpp"
//extern OTSet OTS;
int main(int argc,char ** argv)
{
    
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=2) return 0;
    int port;
    int MyID;
    MyID=atoi(argv[1]);
    port=atoi(argv[2]);
    block D=_mm_set_epi32(0x0,1<<MyID,0xffffffff,0xffffffff);
    //block D=_mm_set_epi32(0,MyID,0,1);
    block seed=_mm_set_epi32(0,0,0,MyID+100);
    Map.Setup(1024);
    IO.Setup(MyID,PartyNumber,port);
    MOT.Setup(MyID,D,10240,seed,&IO);
    MP.Setup(MyID,10240,4,1024,&MOT);
    S.Setup(MyID,128,&MP,&Map);
    //MP.HaAndTest();
    Index array[1024];
    for(int i=0;i<1024;i++)
        array[i]=__pool__NewVar();
    for(int i=2;i<128;i++)
    {
        array[i]=Map.New();
        MP.BatchInput(Map.Read(array[i]),0,1-i%2);
    }
    MP.BatchInputFlush();
    array[1]=__pool__COPY(S.StageMap->Zero);
    array[0]=__pool__COPY(S.StageMap->One);
    auto t=clock_start();
    for(int repeat=0;repeat<30*100;repeat++)
    {
    for(int i=0;i<34;i++)
    {
        __pool__RELEASE(array[128+i]);
        array[128+i]=__pool__AND(array[0],array[i+1]);
    }
    
    for(int i=0;i<34;i++)
    {
        __pool__RELEASE(array[128+34+i]);
        array[128+34+i]=__pool__XOR(array[128+i],array[i+1]);
    }
    for(int i=0;i<34;i++)
    {
        __pool__RELEASE(array[128+i]);
        array[128+i]=__pool__AND(array[0],array[i+1]);
    }
    for(int i=0;i<34;i++)
    {
        __pool__RELEASE(array[128+34+i]);
        array[128+34+i]=__pool__XOR(array[128+i],array[i+1]);
    }
}
    S.Close();
    double t1=time_from(t);
    printf("time=%lf\n",t1/1000000);
    S.PrintCount();
    
//    return 0;
   // for(int i=0;i<10;i++)
     //   MP.CheckLabel(Map.Read(array[128+i]));
    
    
    for(int i=0;i<10;i++)
     {
     if(MyID==0)
     printf("%d ",MP.Reveal(Map.Read(array[128+i])));
     else
         MP.Reveal(Map.Read(array[128+i]));
     }
    printf("\n");
    
    for(int i=10;i<20;i++)
    {
        if(MyID==0)
            printf("%d ",MP.Reveal(Map.Read(array[128+i])));
        else
            MP.Reveal(Map.Read(array[128+i]));
    }

    
     
    /*
    block test[(PartyNumber-1)*2*128*3];
    MP.NewTuples(test,128);
    //MOT.MultiOT(test,128);
    for(int i=0;i<3;i++)
    {
        printf("ID= %d\n",i);
        for(int j=0;j<PartyNumber-1;j++)
        {
            print(test[2*(PartyNumber-1)*i+2*j]);
            print(test[2*(PartyNumber-1)*i+2*j+1]);
            print(_mm_xor_si128(test[2*(PartyNumber-1)*i+2*j+1],D));
            printf("\n");
        }
    }
     */
}

