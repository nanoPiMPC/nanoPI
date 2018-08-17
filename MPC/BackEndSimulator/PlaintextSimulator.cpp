//
//  PlaintextSimulator.cpp
//  
//
//  Created by Sourgroup on 4/22/18.
//
#define InputLength 160000
#include "PlaintextSimulator.hpp"
#include <chrono>
using std::chrono::time_point;
using std::chrono::high_resolution_clock;
long long XORCount=0;
long long ANDCount=0;
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
Index Zero=0,One=1;
void ED(Index *z, Index *x, Index *y);
void AES(Index *x);
void test(Index dst_array[], Index c, Index constc);
void Sort(Index Sign, Index *In, int len);
void AES(Index *input);
void MAES(int n);
void Application();
int main()
{
    Index array[InputLength];
    for(int i=0;i<InputLength;i++)
        array[i]=Input();
    Index result[16];
    for(int i=0;i<16;i++)
        result[i]=__pool__NewVar();
    //  test(array,array[32],array[32]);
    auto t=clock_start();
    Application();
    // Sort(array[32768],array,5000);
    // MAES(1000);
    //    ED(array+8000,array,array+4000);
    double t1=time_from(t);
    printf("AND=%lld XOR=%lld\n",ANDCount,XORCount);
 printf("Time=%lf\n",t1/1000000);
}
