//
//  BackendSimulator.cpp
//  
//
//  Created by Sourgroup on 4/2/18.
//
#define InputLength 5000*32*2
#define wiremapSize 5000*32*4
#include "BackendSimulator.hpp"
#include <chrono>
using std::chrono::time_point;
using std::chrono::high_resolution_clock;

inline void error(const char *msg)
{
    printf("%s\n",msg);
    exit(0);
}

inline time_point<high_resolution_clock> clock_start() {
    return high_resolution_clock::now();
}
inline double time_from(const time_point<high_resolution_clock>& s) {
    return std::chrono::duration_cast<std::chrono::microseconds>(high_resolution_clock::now() - s).count();
}
Index Zero,One;
wiremap Map;
long long XORCount=0;
long long ANDCount=0;
void ED(Index *z, Index *x, Index *y);
void AES(Index *x);
void test(Index dst_array[], Index c, Index constc);
void Sort(Index Sign, Index *In, int len);
void AES(Index *input);
void MAES(int n);
void floatest();
void logreg();
void FixPointTest();
void Application();
int main()
{
    Map.Setup(wiremapSize);
    Zero=Input();
    One=Input();
    Index array[InputLength];
    for(int i=0;i<InputLength;i++)
        array[i]=Input();
    Index result[16];
    for(int i=0;i<16;i++)
        result[i]=__pool__NewVar();
  //  test(array,array[32],array[32]);
    auto t=clock_start();
    Application();
    //floatest();
    //FixPointTest();
    //logreg();
  // floatest();
     //Sort(array[32768],array,5000);
    // MAES(1000);
//    ED(array+8000,array,array+4000);
    double t1=time_from(t);
    __pool__RELEASE(Zero);
    __pool__RELEASE(One);
    CheckLeakage();
    printf("AND=%lld\nXOR=%lld\nTime=%lf\n",ANDCount,XORCount,t1/1000000);
}
