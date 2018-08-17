#include "BackendSimulator.hpp"
#include "float.hpp"
void floatest()
{
    __pool__bool ob[7];
    bool b[7];
    __pool__float of[6];
    float f[6];
    
//    __pool__makeBool(&ob[0],0);
//    __pool__makeBool(&ob[1],1);
    /*
    __pool__makeBool(&ob[2],1);
    __pool__makeBool(&ob[3],1);
    __pool__makeBool(&ob[4],1);
    __pool__makeBool(&ob[5],1);
    */
//    __pool__revealBool(&b[0],&ob[0]);
//    __pool__revealBool(&b[1],&ob[1]);
    
    __pool__makeFloat(&of[0],2.173);
    __pool__makeFloat(&of[1],3.14159);
//    __pool__makeFloat(&of[2],0);
//    __pool__makeFloat(&of[3],0);
//    __pool__makeFloat(&of[4],0);
//    __pool__makeFloat(&of[5],0);
    __pool__floatAdd(&(of[2]),&(of[0]),&(of[1]));
    __pool__revealFloat(&(f[0]),&(of[0]));
    __pool__revealFloat(&(f[1]),&(of[1]));
    __pool__revealFloat(&(f[2]),&(of[2]));
    printf("%f %f %f\n",f[0],f[1],f[2]);
    for(int i=0;i<32;i++)
    {
        printf("%d\n",of[0].bits[i]);
    }
    for(int i=0;i<32;i++)
    {
        printf("%d\n",of[1].bits[i]);
    }
    for(int i=0;i<32;i++)
    {
        printf("%d\n",of[2].bits[i]);
    }

    
   // __pool__releaseFloat(&(of[0]));
   // __pool__releaseFloat(&(of[1]));
   
    //__pool__releaseFloat(&(of[0]));
   // __pool__releaseFloat(&(of[1]));
    return;
    /*
    __pool__floatSub(&(of[3]),&(of[0]),&(of[1]));
    __pool__floatMul(&(of[4]),&(of[0]),&(of[1]));
    __pool__floatDiv(&(of[5]),&(of[0]),&(of[1]));
    __pool__floatLt(&(ob[2]),&(of[0]),&(of[1]));
    __pool__floatLe(&(ob[3]),&(of[0]),&(of[1]));
    __pool__floatGt(&(ob[4]),&(of[0]),&(of[1]));
    __pool__floatGe(&(ob[5]),&(of[0]),&(of[1]));
    */

    __pool__releaseBool(&ob[0]);
    __pool__releaseBool(&ob[1]);
    __pool__releaseBool(&ob[2]);
    __pool__releaseBool(&ob[3]);
    __pool__releaseBool(&ob[4]);
    __pool__releaseBool(&ob[5]);
    
    __pool__releaseFloat(&(of[0]));
    __pool__releaseFloat(&(of[1]));
    __pool__releaseFloat(&(of[2]));
    __pool__releaseFloat(&(of[3]));
    __pool__releaseFloat(&(of[4]));
    __pool__releaseFloat(&(of[5]));
    
}
