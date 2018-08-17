//
//  Network_IO.cpp
//
//
//  Created by Sourgroup on 10/24/17.
//

#include "Network_IO.hpp"
Network IO;
int exchangeid=0;
#ifndef NaiveIO
ThreadPool pool((PartyNumber-1)*2);
#endif
unsigned char Network::psend(int id,void *m, int n,bool F)
{
#ifdef IOTimer
    auto t0=clock_start();
#endif
    int s;
    if(id<MyID)
    {
        s=fwrite((unsigned char*)m,sizeof(unsigned char),n,stream[2*id+1]);
    }
    else{
    if(id>MyID)
    {
        s=fwrite((unsigned char*)m,sizeof(unsigned char),n,stream[2*id]);
    }
        
    }
    if(s!=n) printf("fwrite error!\n");
    if(F)
    {
        if(id<MyID)
            fflush(stream[2*id+1]);
        if(id>MyID)
            fflush(stream[2*id]);
    }
#ifdef IOTimer
    Monitor[2*id+1].lock();
    outByte[id]+=n;
    outtime[id]+=time_from(t0);
    Monitor[2*id+1].unlock();
//    printf("Send %lf %lf\n",n*1.0/1000000,time_from(t0)/1000000);
#endif
    return true;
}
unsigned char Network::preceive(int id,void *m, int n)
{
#ifdef IOTimer
    auto t0=clock_start();
#endif
    int s;
    if(id<MyID)
        s=fread((unsigned char*)m,sizeof(unsigned char),n,stream[id*2]);
    else{
    if(id>MyID)
        s=fread((unsigned char*)m,sizeof(unsigned char),n,stream[id*2+1]);
    }
    if(s!=n) {
        printf("fread error! %d %d\n",s,n);
        
        exit(0);
    }
#ifdef IOTimer
        Monitor[2*id].lock();
    inByte[id]+=n;
    intime[id]+=time_from(t0);
        Monitor[2*id].unlock();
//    printf("Receive %lf %lf\n",time_from(t0)/1000000,outtime);
#endif

    return ((unsigned char*)m)[0];
}
void Network::Setup(int id,int NofP,int portno0)
{
    if(NofP>MaxPartyNum)error("Too Many Parties");
    MyID=id;
    #ifdef IOTimer
    for(int i=0;i<PartyNumber;i++)
    {
        intime[i]=0;
        outtime[i]=0;
        inByte[i]=0;
        outByte[i]=0;
    }
#endif
    for(int i=0;i<PartyNumber;i++)
    {
        if(id<i)
        {
            int port0=portno0+(NofP*2-1-id)*id/2;
            server_open_socket(2*i,2*i+1,port0+i-id-1);
        }
        if(id>i)
        {
            int port0=portno0+(NofP*2-1-i)*i/2;
            client_open_socket(2*i,2*i+1,i,port0+id-i-1);
        }
    }
#ifndef NaiveIO
  //  threads.resize(2*(PartyNumber-1));
#endif
}
void Network::flush(int id)
{
    if(id<MyID)
        fflush(stream[id*2+1]);
    if(id>MyID)
        fflush(stream[id*2]);
}
void Network::exchange(void *dst[],void *src[],int size)
{
#ifndef NaiveIO
    std::future<unsigned char> future[PartyNumber];
#endif
    for(int i=0;i<PartyNumber;i++)
    {
        if(i!=MyID)
        {
#ifndef NaiveIO
            if(i<MyID)
                future[i]=pool.enqueue(Send_and_Receive,0,this,i,dst[i],src[i],size,size);//threads.push(Send_and_Receive,this,i,dst[i],src[i],size,size);
            else
                future[i]=pool.enqueue(Receive_and_Send,0,this,i,dst[i],src[i],size,size);//threads.push(Receive_and_Send,this,i,dst[i],src[i],size,size);
#else
            if(i<MyID)
            {
                PsendHelper(0,this,i,src[i],size,true);
                PreceiveHelper(0,this,i,dst[i],size);
            }
            else
            {
                PreceiveHelper(0,this,i,dst[i],size);
                PsendHelper(0,this,i,src[i],size,true);
            }
#endif
        }
    }
#ifndef NaiveIO
    unsigned char t;
    for(int i=0;i<PartyNumber;i++)
        if(i!=MyID)
        {
            t=future[i].get();
        }
#endif
}
void Network::advexchange(void *dst[],void *src[],int size[])
{
#ifndef NaiveIO
    std::future<unsigned char> future[PartyNumber];
#endif
    for(int i=0;i<PartyNumber;i++)
    {
        if(i!=MyID)
        {
#ifndef NaiveIO
 if(i<MyID)
     future[i]=pool.enqueue(Send_and_Receive,0,this,i,dst[i],src[i],size[2*i+1],size[2*i]);
            //threads.push(Send_and_Receive,this,i,dst[i],src[i],size[2*i+1],size[2*i]);
            else
                future[i]=pool.enqueue(Receive_and_Send,0,this,i,dst[i],src[i],size[2*i+1],size[2*i]);//threads.push(Receive_and_Send,this,i,dst[i],src[i],size[2*i+1],size[2*i]);
            
#else
            if(i<MyID)
            {
                PsendHelper(0,this,i,src[i],size[2*i],true);
                PreceiveHelper(0,this,i,dst[i],size[2*i+1]);
            }
            else
            {
                PreceiveHelper(0,this,i,dst[i],size[2*i+1]);
                PsendHelper(0,this,i,src[i],size[2*i],true);
            }
#endif
        }
    }
#ifndef NaiveIO
    unsigned char t;
    for(int i=0;i<PartyNumber;i++)
        if(i!=MyID)
        {
            t=future[i].get();
        }
#endif
}
void Network::doublexchange(void *dst1[], void *dst2[],void *src1[],void *src2[],int size1,int size2)
{
#ifndef NaiveIO
    std::future<unsigned char> future[PartyNumber];
#endif
    for(int i=0;i<PartyNumber;i++)
    {
        if(i!=MyID)
        {
#ifndef NaiveIO
           // future[i]=threads.push(PsendHelper2,this,i,src1[i],src2[i],size1,size2);
          //  future[i+PartyNumber]=threads.push(PreceiveHelper2,this,i,dst1[i],dst2[i],size1,size2);
            if(i<MyID)
                future[i]=pool.enqueue(Send_and_Receive2,0,this,i,dst1[i],dst2[i],src1[i],src2[i],size1,size2);//threads.push(Send_and_Receive2,this,i,dst1[i],dst2[i],src1[i],src2[i],size1,size2);
            else
                future[i]=pool.enqueue(Receive_and_Send2,0,this,i,dst1[i],dst2[i],src1[i],src2[i],size1,size2);//threads.push(Receive_and_Send2,this,i,dst1[i],dst2[i],src1[i],src2[i],size1,size2);
            
#else
            if(i<MyID){
                PsendHelper2(0,this,i,src1[i],src2[i],size1,size2);
                PreceiveHelper2(0,this,i,dst1[i],dst2[i],size1,size2);
            }
            else
            {
                PreceiveHelper2(0,this,i,dst1[i],dst2[i],size1,size2);
                PsendHelper2(0,this,i,src1[i],src2[i],size1,size2);
            }
#endif
        }
    }
#ifndef NaiveIO
    unsigned char t;
    for(int i=0;i<PartyNumber;i++)
        if(i!=MyID)
        {
            t=future[i].get();
        }
#endif
}
void Network::gather(int id,void *src,int size)
{
    if(id==MyID) {
        printf("Wrong gather id %d %d\n",id,MyID);
    }
#ifndef NaiveIO
    auto future=pool.enqueue(PsendHelper,0,this,id,src,size,false);//threads.push(PsendHelper,this,id,src,size,false);
    unsigned char t=future.get();
#else
    PsendHelper(0,this,id,src,size,false);
#endif
}
void Network::gather(int id,void *dst[],int size)
{
    if(id!=MyID) {
        printf("Wrong gather id %d %d\n",id,MyID);
    }
#ifndef NaiveIO
    std::future<unsigned char> future[PartyNumber];
#endif
    for(int i=0;i<PartyNumber;i++)
        if(i!=MyID)
        {
#ifndef NaiveIO
            future[i]=pool.enqueue(PreceiveHelper,0,this,i,dst[i],size);//threads.push(PreceiveHelper,this,i,dst[i],size);
#else
            PreceiveHelper(0,this,i,dst[i],size);
#endif
        }
#ifndef NaiveIO
    unsigned char t;
    for(int i=0;i<PartyNumber;i++)
        if(i!=MyID)
        {
            t=future[i].get();
        }
#endif
}
/*
 void Network::broadcast(int id,void *dst,int size)
 {
 if(id==MyID) {
 printf("Wrong gather id %d %d\n",id,MyID);
 }
 preceive(id,dst,size);
 }
 void Network::broadcast(int id,void *src[],int size)
 {
 if(id!=MyID) {
 printf("Wrong gather id %d %d\n",id,MyID);
 }
 for(int i=0;i<PartyNumber;i++)
 if(i!=MyID)
 psend(i,src[i],size);
 }
 */
void Network::server_open_socket(int id1,int id2,int portno)
{
    int sockfd, newsockfd,newsockfddup;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    int on=1;
    if((setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)))<0)
    {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *) &cli_addr,
                       &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");
    newsockfddup=dup(newsockfd);
    if (newsockfddup < 0)
        error("ERROR on DUP");
    close(sockfd);
    stream[id1]= fdopen(newsockfd, "w");
    stream[id2]= fdopen(newsockfddup,"r");
    printf("connected Server at %d\n",portno);
    return;
}
void Network::client_open_socket(int id1,int id2,int id, int portno)
{
    int sockfd,sockfddup;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(HostAddress[id]);//gethostbyname(argv[1]);
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    while(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) == -1) {
        usleep(1000);
    }
    sockfddup=dup(sockfd);
    if (sockfddup < 0)
        error("ERROR on DUP");
    stream[id1]= fdopen(sockfd, "r");
    stream[id2]= fdopen(sockfddup, "w");
    printf("connected Clinet at %d\n",portno);
    return;
}

