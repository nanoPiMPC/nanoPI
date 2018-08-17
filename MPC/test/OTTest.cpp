//
//  OTTest.cpp
//  
//
//  Created by Sourgroup on 1/8/18.
//

#include <stdio.h>
#include "MOTE.hpp"
#include "OTE.hpp"
/*void test(int id)
{
    for(int i=0;i<100;i++)
        printf("%d %d\n",id,i);
}
 */
//extern OTSet OTS;
int main(int argc,char ** argv)
{
    
    printf("Party Num=%d\n",PartyNumber);
    if(argc<=2) return 0;
    int port;
    int MyNumber;
    MyNumber=atoi(argv[1]);
    port=atoi(argv[2]);
    IO.Setup(MyNumber,PartyNumber,port);
    block D=_mm_set_epi32(0,MyNumber,0,1);
    block test[(PartyNumber-1)*2*20480];
    OTSet OTS[PartyNumber-1];
    block seed=_mm_set_epi32(0,0,0,MyNumber+100);
    int index=0;
    MOT.Setup(MyNumber,D,1024,seed,&IO);
    MOT.MultiOT(test,20480);
    for(int i=0;i<10;i++)
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
}
