//
//  Network_IO.hpp
//
//
//  Created by Sourgroup on 10/24/17.
//

#ifndef Network_IO_hpp
#define Network_IO_hpp
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <stdlib.h>
#include <functional>
#ifdef IOTimer
#include <mutex>
#endif
#ifndef NaiveIO
#include "ThreadPool.h"
#endif
#include "util.hpp"
#define MaxPartyNum 8
#define Address1 "127.0.0.1"
#define Address2 "127.0.0.1"
#define Address3 "127.0.0.1"
#define Address4 "127.0.0.1"
#define Address5 "127.0.0.1"
#define Address6 "127.0.0.1"
#define Address7 "127.0.0.1"
#define Address8 "127.0.0.1"

// Network API Warpper
class Network{
private:
#ifdef IOTimer
    std::mutex Monitor[PartyNumber*2];
    double intime[PartyNumber];
    double outtime[PartyNumber];
#endif
#ifndef Lab
    const char *HostAddress[MaxPartyNum]={Address1,Address2,Address3,Address4,Address5,Address6,Address7,Address8};
#else
   const char *HostAddress[MaxPartyNum]={Address1,Address2,Address3,Address4,Address5,Address6,Address7,Address8,Address9,Address10,Address11,Address12,Address13,Address14,Address15,Address16};
#endif
    int MyID;
    int TotalPartyNum=PartyNumber;
    FILE *stream[PartyNumber*2];
    unsigned char preceive(int id,void *m, int n);
    unsigned char psend(int id,void *m, int n,bool F);

public:
    friend unsigned char PsendHelper(int tid,Network *IO,int id,void *m, int n,bool F);
    friend unsigned char PreceiveHelper(int tid,Network *IO,int id,void *m, int n);
    friend unsigned char PsendHelper2(int tid,Network *IO,int id,void *m1, void *m2, int n1,int n2);
    friend unsigned char PreceiveHelper2(int tid,Network *IO,int id,void *m1, void *m2, int n1,int n2);
    friend unsigned char Send_and_Receive(int tid,Network *IO,int id,void *dst,void *src, int n1,int n2);
    friend unsigned char Receive_and_Send(int tid,Network *IO,int id,void *dst,void *src, int n1,int n2);
    friend unsigned char Send_and_Receive2(int tid,Network *IO,int id,void *dst1,void *dst2,void *src1,void *src2, int n1, int n2);
    friend unsigned char Receive_and_Send2(int tid,Network *IO,int id,void *dst1,void *dst2,void *src1,void *src2, int n1, int n2);
    #ifdef IOTimer
    unsigned long long inByte[MaxPartyNum],outByte[MaxPartyNum];
#endif
    void client_open_socket(int id1,int id2,int id,int portno);
    void server_open_socket(int id1,int id2,int portno);
    void flush(int id);
    void Setup(int id,int NofP,int portno0);
    void exchange(void *dst[],void *src[],int size);
    void advexchange(void *dst[],void *src[],int size[]);
    void doublexchange(void *dst1[],void *dst2[],void *src1[],void *src2[],int size1,int size2);
    void gather(int id,void *src,int size);
    void gather(int id,void *dst[],int size);
   // void broadcast(int id,void *dst,int size);
   // void broadcast(int id,void *src[],int size);
    void PrintCount()
    {
#ifdef IOTimer
        printf("Network Usage:\n");
        unsigned long long in=0,out=0;
        double it=0,ot=0;
        for(int i=0;i<PartyNumber;i++)
        {
            Monitor[2*i].lock();
            it+=intime[i];
            in+=inByte[i];
            intime[i]=0;
            inByte[i]=0;
            Monitor[2*i].unlock();
            Monitor[2*i+1].lock();
            out+=outByte[i];
            ot+=outtime[i];
            outtime[i]=0;
            outByte[i]=0;
            Monitor[2*i+1].unlock();
        }
        printf("InByte(MB) %lf\nOutByte(MB) %lf\n",in*1.0/1000000,out*1.0/1000000);
        printf("Intime %lf\nOuttime %lf\n",it/1000000,ot/1000000);
 #endif
}
};
extern Network IO;
/*
inline void BroadCast(Network *IO,int id,void *dst,int size)
{
    IO->broadcast(id,dst,size);
}
inline void BroadCast(Network *IO,int id,void *src[],int size)
{
    IO->broadcast(id,src,size);
}
 */
inline void Gather(Network *IO,int id,void *src,int size)
{
    IO->gather(id,src,size);
}
inline void Gather(Network *IO,int id,void *dst[],int size)
{
    IO->gather(id,dst,size);
}
inline void Exchange(Network *IO,void *dst[],void *src[],int size)
{
    IO->exchange(dst,src,size);
}
inline void AdvExchange(Network *IO,void *dst[],void *src[],int size[])
{
    IO->advexchange(dst,src,size);
}
inline void DoublExchange(Network *IO,void *dst1[],void *dst2[],void *src1[],void *src2[],int size1,int size2)
{
    IO->doublexchange(dst1,dst2,src1,src2,size1,size2);
}

inline unsigned char PsendHelper(int tid,Network *IO,int id,void *m, int n,bool F)
{
    return IO->psend(id,m,n,F);
}

inline unsigned char PreceiveHelper(int tid,Network *IO,int id,void *m, int n)
{
    return IO->preceive(id,m,n);
}
inline unsigned char PsendHelper2(int tid,Network *IO,int id,void *m1, void *m2, int n1,int n2)
{
    IO->psend(id,m1,n1,false);
    IO->psend(id,m2,n2,true);
//    IO->flush(id);
    return true;
}

inline unsigned char PreceiveHelper2(int tid,Network *IO,int id,void *m1, void *m2, int n1,int n2)
{
    IO->preceive(id,m1,n1);
    return IO->preceive(id,m2,n2);
}
inline unsigned char Send_and_Receive(int tid,Network *IO,int id,void *dst,void *src, int n2,int n1)
{
    IO->psend(id,src,n1,true);
    IO->preceive(id,dst,n2);
    return true;
}
inline unsigned char Receive_and_Send(int tid,Network *IO,int id,void *dst,void *src, int n2,int n1)
{
    IO->preceive(id,dst,n2);
    IO->psend(id,src,n1,true);
    return true;
}
inline unsigned char Send_and_Receive2(int tid,Network *IO,int id,void *dst1,void *dst2,void *src1,void *src2, int n1, int n2)
{
    IO->psend(id,src1,n1,false);
    IO->psend(id,src2,n2,true);
    IO->preceive(id,dst1,n1);
    IO->preceive(id,dst2,n2);
    return true;
}
inline unsigned char Receive_and_Send2(int tid,Network *IO,int id,void *dst1,void *dst2,void *src1,void *src2, int n1, int n2)
{
    IO->preceive(id,dst1,n1);
    IO->preceive(id,dst2,n2);
    IO->psend(id,src1,n1,false);
    IO->psend(id,src2,n2,true);
    return true;
}





#endif /* Network_IO_hpp */
