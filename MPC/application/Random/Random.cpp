//
//  ApplicationExecution.cpp
//  
//
//  Created by Sourgroup on 3/26/18.
//

#include "Stage.hpp"
#ifdef B3
#define MainPoolSize 479000
#define MainBucketSize 3
#endif
#ifdef B4
#define MainPoolSize 8000
//#define MainStageSize 8000
//#define MainBuffer 8000
//#define MainWireArraySize 40000
#define MainBucketSize 4
#endif
#ifdef Random
#define N 1
void Application()
{
    extern Index Zero,One;
    Index array[N];
    for(int i=0;i<N;i++)
        array[i]=__pool__COPY(One);
    auto t0=clock_start();
    for(int i=0;i<100000;i++)
    {
        for(int j=0;j<N;j++)
        {
            Index tmp;
            tmp=__pool__AND(array[j],One);
            __pool__RELEASE(tmp);
/*           for(int k=0;k<3;k++)
            {
                tmp=__pool__XOR(array[j],One);
                __pool__RELEASE(tmp);
            }
  */
      }
    }
    __pool__RELEASEArray(array,N);
    S.Close();
    S.PrintCount();
    double t1=time_from(t0);
    printf("Time=%lf\n",t1/1000000);
}
#endif
Index Zero,One;
void Application();
int main(int argc,char ** argv)
{
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=3) return 0;
    int port;
    int MyID;
    MyID=atoi(argv[1]);
    port=atoi(argv[2]);
    block D=_mm_set_epi32(0x0,1<<MyID,0xffffffff,0xffffffff);
    //block D=_mm_set_epi32(0,MyID,0,1);
    block seed=_mm_set_epi32(0,0,0,MyID+100);
    int Scale=atoi(argv[3]);
    int MainStageSize=1280*Scale;
    int MainBuffer=1280*Scale;
    int MainWireArraySize=65000*Scale;
    IO.Setup(MyID,PartyNumber,port);
    auto t=clock_start();
    Map.Setup(MainWireArraySize);
    MOT.Setup(MyID,D,MainBuffer,seed,&IO);
    MP.Setup(MyID,MainPoolSize,MainBucketSize,MainBuffer,&MOT);
    S.Setup(MyID,MainStageSize,&MP,&Map);
    Zero=Map.Zero;
    One=Map.One;
    printf("Setup cost: %lfs\n",time_from(t)/1000000);
    IO.PrintCount();
    Application();
}
