//
//  ApplicationExecution.cpp
//  
//
//  Created by Sourgroup on 3/26/18.
//

#include "Stage.hpp"
#define Scale 100
#ifdef B3
#define MainPoolSize 479000
#define MainStageSize 1280*Scale
#define MainBuffer 1280*Scale
#define MainWireArraySize 4000000+MainStageSize
#define MainBucketSize 3
#endif
#ifdef B4
#define MainPoolSize 8000
#define MainStageSize 8000
#define MainBuffer 8000
#define MainWireArraySize 40000
#define MainBucketSize 4
#endif
Index Zero,One;
void Application();
int main(int argc,char ** argv)
{
    auto t=clock_start();
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=2) return 0;
    int port;
    int MyID;
    MyID=atoi(argv[1]);
    port=atoi(argv[2]);
    block D=_mm_set_epi32(0x0,1<<MyID,0xffffffff,0xffffffff);
    //block D=_mm_set_epi32(0,MyID,0,1);
    block seed=_mm_set_epi32(0,0,0,MyID+100);
    Map.Setup(MainWireArraySize);
    IO.Setup(MyID,PartyNumber,port);
    MOT.Setup(MyID,D,MainBuffer,seed,&IO);
    MP.Setup(MyID,MainPoolSize,MainBucketSize,MainBuffer,&MOT);
    S.Setup(MyID,MainStageSize,&MP,&Map);
    Zero=Map.Zero;
    One=Map.One;
    printf("Setup cost: %lfs\n",time_from(t)/1000000);
    IO.PrintCount();
    Application();
}
