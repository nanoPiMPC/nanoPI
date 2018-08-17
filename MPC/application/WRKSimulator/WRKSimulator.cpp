//
//  ApplicationExecution.cpp
//  
//
//  Created by Sourgroup on 3/26/18.
//

#include "Stage.hpp"
void Application(int N)
{
    extern Index Zero,One;
    Index array[N+1];
    auto t0=clock_start();
    for(int i=0;i<10;i++)
    {
        array[0]=__pool__COPY(One);
        for(int j=0;j<N;j++)
        {
            Index tmp;
            for(int k=0;k<3;k++)
            {
                tmp=__pool__XOR(array[0],One);
                __pool__RELEASE(tmp);
            }
            array[j+1]=__pool__AND(array[0],One);
        }
        __pool__RELEASEArray(array,N+1);
    }
    S.Close();
    double t1=time_from(t0);
    S.PrintCount();
    printf("Time=%lf\n",t1/1000000);
}
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
    int bucketsize=3;
    int N=atoi(argv[3]);
    if(N<320) {
        printf("too small\n");
        exit(0);
    }
    if(N<280000)
    {
        bucketsize=4;
    }
    if(N<3100)
    {
        bucketsize=5;
    }
    int MainStageSize=N;
    int MainWireArraySize=N*10;
    
    IO.Setup(MyID,PartyNumber,port);
    auto t=clock_start();
    Map.Setup(MainWireArraySize);

    MOT.Setup(MyID,D,(((bucketsize*3+1)*N)/128+1)*128,seed,&IO);
    
    MP.AdvSetup(MyID,1024,bucketsize,N,bucketsize*N*3+N,N,N,&MOT);
    
    S.Setup(MyID,MainStageSize,&MP,&Map);
    Zero=Map.Zero;
    One=Map.One;
    printf("Setup cost: %lfs\n",time_from(t)/1000000);
    IO.PrintCount();
    Application(N);
}
