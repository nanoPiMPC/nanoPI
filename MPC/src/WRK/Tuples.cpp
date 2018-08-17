//
//  Tuples.cpp
//  
//
//  Created by Sourgroup on 12/22/17.
//

#include "Tuples.hpp"
void MPool::NewTuples(block *dst, int n)
{
    while(n+TupleBufferIndex>TupleBufferSize)
    {
        int i=TupleBufferSize-TupleBufferIndex;
        memcpy(dst,&(TupleBuffer[TupleBufferIndex*3*2*(PartyNumber-1)]),16*6*(PartyNumber-1)*i);
        CombineTuples();
        dst=dst+i*3*2*(PartyNumber-1);
        TupleBufferIndex=0;
        n=n-i;
    }
    memcpy(dst,&(TupleBuffer[TupleBufferIndex*6*(PartyNumber-1)]),16*6*(PartyNumber-1)*n);
    TupleBufferIndex+=n;
}


void MPool::HaAnd(unsigned char *dst, block *src, int n,block *hashbed)
{
    unsigned char *s=new unsigned char[(PartyNumber-1)*n+(((PartyNumber-1)*n) & 1)];
    unsigned char *rcvdh=new unsigned char[(PartyNumber-1)*n];
    block *tmps=new block[((PartyNumber-1)*n+127)/128];
    PRG(tmps,((PartyNumber-1)*n+127)/128,&Public_AES_KEY,&Public_Count);
    for(int i=0;i<(PartyNumber-1)*n;i+=2)
    {
        s[i]=_mm_extract_epi8(tmps[i/128],0)&1;
        s[i]+=s[i]<<1;
        s[i+1]=_mm_extract_epi8(tmps[i/128],8)&1;
        s[i+1]+=s[i+1]<<1;
        tmps[i/128]=_mm_srli_epi64(tmps[i/128],1);
    }
    for(int i=0;i<n;i++)
    {
        dst[i]=extract_bit(hashbed[(PartyNumber-1)*3*i+2]);
        for(int j=1;j<PartyNumber-1;j++)
        {
            dst[i]^=extract_bit(hashbed[(PartyNumber-1)*3*i+2+3*j]);
        }
    }
    
    for(int j=0;j<PartyNumber-1;j++)
    {
        for(int i=0;i<n;i++)
        {
            dst[i]^=(s[i+j*n]& 1);
        }
    }
    for(int i=0;i<n;i++)
    {
        unsigned char tmp;
        tmp=extract_bit(src[6*(PartyNumber-1)*i+2*(PartyNumber-1)]);
        tmp=tmp<<1;
        for(int j=0;j<PartyNumber-1;j++)
            s[i+j*n]^=tmp;
    }
    for(int j=0;j<PartyNumber-1;j++)
        for(int i=0;i<n;i++)
        {
            s[i+j*n]^=extract_bit(hashbed[i*(PartyNumber-1)*3+j*3]);
            s[i+j*n]^=(extract_bit(hashbed[i*(PartyNumber-1)*3+j*3+1]))<<1;
        }
    void *exsrc[PartyNumber];
    void *exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&(s[n*i]);
            exdst[i]=&(rcvdh[n*i]);
        }
        if(i>MyID)
        {
            exsrc[i]=&(s[n*(i-1)]);
            exdst[i]=&(rcvdh[n*(i-1)]);
        }
    }
    Exchange(IO,exdst,exsrc,n);

    for(int i=0;i<n;i++)
    {
        unsigned char tmp;
        tmp=extract_bit(src[6*(PartyNumber-1)*i]);
        for(int j=0;j<PartyNumber-1;j++)
        {
            if(tmp==0)
                dst[i]^=(rcvdh[j*n+i] & 1);
            else
                dst[i]^=((rcvdh[j*n+i]>>1) & 1);
        }
    }
    delete[] s;
    delete[] rcvdh;
    delete[] tmps;
}


void MPool::NewLeakyTuples(block *src,int n)
{
    unsigned char *bit=(unsigned char*)malloc(sizeof(unsigned char)*(n*PartyNumber));
    NewBits(src,3*n);
    block *hashbed=(block*)_mm_malloc(sizeof(block)*(n*(PartyNumber-1)*3*2),16);
    for(int i=0;i<n;i++)
        for(int j=0;j<(PartyNumber-1);j++)
        {
            hashbed[3*(PartyNumber-1)*i+3*j]=src[(PartyNumber-1)*6*i+2*j+1];
            hashbed[3*(PartyNumber-1)*i+3*j+1]=_mm_xor_si128(src[(PartyNumber-1)*6*i+2*j+1],Delta);
            hashbed[3*(PartyNumber-1)*i+3*j+2]=src[(PartyNumber-1)*6*i+2*j];
        }
    memcpy(&(hashbed[n*(PartyNumber-1)*3]),hashbed,16*n*(PartyNumber-1)*3);
    AES_ecb_encrypt_blks(hashbed,n*(PartyNumber-1)*3,&Public_AES_KEY);
    for(int i=0;i<n*(PartyNumber-1)*3;i++)
        hashbed[i]=_mm_xor_si128(hashbed[i],hashbed[i+n*(PartyNumber-1)*3]);

    HaAnd(bit+MyID*n,src,n,hashbed);
    for(int i=0;i<n;i++)
    {
        bit[MyID*n+i]^=extract_bit(src[6*(PartyNumber-1)*i])
        *extract_bit(src[6*(PartyNumber-1)*i+2*(PartyNumber-1)])
        ^extract_bit(src[6*(PartyNumber-1)*i+4*(PartyNumber-1)]);
    }
    void *exsrc[PartyNumber];
    void *exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(bit[MyID*n]);
        exdst[i]=&(bit[n*i]);
    }
    Exchange(IO,exdst,exsrc,n);

    for(int j=1;j<PartyNumber;j++)
    {
        for(int i=0;i<n;i++)
        {
            bit[i]^=bit[i+n*j];
        }
    }
    if(MyID==0)
    {
        for(int i=0;i<n;i++)
        {
            if(bit[i]!=0)
            {
                for(int j=0;j<PartyNumber-1;j++)
                    src[6*(PartyNumber-1)*i+4*(PartyNumber-1)+j*2]=_mm_xor_si128(src[6*(PartyNumber-1)*i+4*(PartyNumber-1)+j*2],plainbit1);
            }
        }
    }
    else{
        for(int i=0;i<n;i++)
        {
            if(bit[i]!=0)
            {
                src[6*(PartyNumber-1)*i+4*(PartyNumber-1)+1]=_mm_xor_si128(src[6*(PartyNumber-1)*i+4*(PartyNumber-1)+1],delta);
            }
        }
    }
    CheckTuples(src,n,hashbed);
    free(bit);
    _mm_free(hashbed);
    return;
}
void MPool::CheckTuples(block *src, int n,block *hashbed)
{
    block *phi=new block[n];
    block *u=new block[n*(PartyNumber-1)];
    block *recvu=new block[n*(PartyNumber-1)];
    block *M=new block[n*(PartyNumber-1)];
    block *allH=new block[n*PartyNumber];
    block *H=allH+n*MyID;
    for(int i=0;i<n;i++)
    {
        if(extract_bit(src[(PartyNumber-1)*6*i+2*(PartyNumber-1)])==0)
        {
            phi[i]=zeroblock;
        }
        else
        {
            phi[i]=Delta;
        }
        for(int j=0;j<(PartyNumber-1)*2;j++)
        {
            phi[i]=_mm_xor_si128(phi[i],src[(PartyNumber-1)*6*i+2*(PartyNumber-1)+j]);
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<PartyNumber-1;j++)
        {
            u[i+j*n]=_mm_xor_si128(phi[i],hashbed[3*(PartyNumber-1)*i+3*j]);
            u[i+j*n]=_mm_xor_si128(u[i+j*n],hashbed[3*(PartyNumber-1)*i+3*j+1]);
        }
    }
    void *exsrc[PartyNumber];
    void *exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            exsrc[i]=&(u[i*n]);
            exdst[i]=&(recvu[i*n]);
        }
        if(i>MyID)
        {
            exsrc[i]=&(u[(i-1)*n]);
            exdst[i]=&(recvu[(i-1)*n]);
        }
    }
    Exchange(IO,exdst,exsrc,16*n);

    for(int i=0;i<n;i++)
    {
        if(extract_bit(src[6*(PartyNumber-1)*i])==0)
        {
            for(int j=0;j<PartyNumber;j++)
            {
                if(j<MyID)
                {
                    M[(PartyNumber-1)*i+j]=hashbed[3*(PartyNumber-1)*i+3*j+2];
                }
                if(j>MyID)
                {
                    M[(PartyNumber-1)*i+j-1]=hashbed[3*(PartyNumber-1)*i+3*(j-1)+2];
                }
            }
        }
        else
        {
            for(int j=0;j<PartyNumber;j++)
            {
                if(j<MyID)
                {
                    M[(PartyNumber-1)*i+j]=_mm_xor_si128(hashbed[3*(PartyNumber-1)*i+3*j+2],recvu[j*n+i]);
                }
                if(j>MyID)
                {
                    M[(PartyNumber-1)*i+j-1]=_mm_xor_si128(hashbed[3*(PartyNumber-1)*i+3*(j-1)+2],recvu[(j-1)*n+i]);
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(extract_bit(src[6*(PartyNumber-1)*i])!=0)
            H[i]=phi[i];
        else
            H[i]=zeroblock;
        for(int j=0;j<PartyNumber-1;j++)
        {
            H[i]=_mm_xor_si128(H[i],M[(PartyNumber-1)*i+j]);
        }
        for(int j=0;j<PartyNumber-1;j++)
        {
            H[i]=_mm_xor_si128(H[i],hashbed[(PartyNumber-1)*3*i+3*j]);
        }
        for(int j=0;j<(PartyNumber-1)*2;j++)
        {
            H[i]=_mm_xor_si128(H[i],src[6*(PartyNumber-1)*i+4*(PartyNumber-1)+j]);
        }
        if(extract_bit(src[6*(PartyNumber-1)*i+4*(PartyNumber-1)])!=0)
        {
            H[i]=_mm_xor_si128(H[i],Delta);
        }
    }
    
    delete[] phi;
    delete[] u;
    delete[] recvu;
    delete[] M;
    
    unsigned char tmp[SHA256_DIGEST_LENGTH];
    unsigned char *allHashofH=new unsigned char[SHA256_DIGEST_LENGTH*PartyNumber];
    SHA256((unsigned char*)H,16*n,allHashofH+SHA256_DIGEST_LENGTH*MyID);
    for(int i=0;i<PartyNumber;i++)
    {
            exsrc[i]=&(allHashofH[MyID*SHA256_DIGEST_LENGTH]);
            exdst[i]=&(allHashofH[i*SHA256_DIGEST_LENGTH]);
    }
    Exchange(IO,exdst,exsrc,SHA256_DIGEST_LENGTH);

    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(allH[MyID*n]);
        exdst[i]=&(allH[i*n]);
    }
    Exchange(IO,exdst,exsrc,n*16);

    for(int i=0;i<PartyNumber;i++)
    {
        if(i!=MyID)
        {
            SHA256((unsigned char*)(&(allH[n*i])),16*n,tmp);
            for(int j=0;j<SHA256_DIGEST_LENGTH;j++)
            {
                if(tmp[j]!=allHashofH[j+i*SHA256_DIGEST_LENGTH])
                    printf("hash error\n");
            }
        }
    }
    
    for(int i=1;i<PartyNumber;i++)
    {
        for(int j=0;j<n;j++)
            allH[j]=_mm_xor_si128(allH[j],allH[i*n+j]);
    }
    /*
    for(int i=2;i<3;i++)
    {
        for(int j=0;j<(PartyNumber-1)*2;j++)
            print(src[i*6*(PartyNumber-1)+j]);
        printf("\n");
        for(int j=0;j<(PartyNumber-1)*2;j++)
            print(src[i*6*(PartyNumber-1)+2*(PartyNumber-1)+j]);
        printf("\n");
        for(int j=0;j<(PartyNumber-1)*2;j++)
            print(src[i*6*(PartyNumber-1)+4*(PartyNumber-1)+j]);
    }
      */
    for(int i=0;i<n;i++)
        if(_mm_testz_si128(allH[i],all1)!=1)
        {
            printf("Tuple error! %d\n",i);
        //    print(allH[i]);
            printf("\n");
            for(int j=0;j<2*(PartyNumber-1);j++)
                print(src[(PartyNumber-1)*6*i+j]);
            printf("\n");
            for(int j=0;j<2*(PartyNumber-1);j++)
                print(src[(PartyNumber-1)*6*i+j+2*(PartyNumber-1)]);
            printf("\n");
            for(int j=0;j<2*(PartyNumber-1);j++)
                print(src[(PartyNumber-1)*6*i+j+4*(PartyNumber-1)]);
            printf("\n");
            exit(0);
        }
    delete[] allH;
    delete[] allHashofH;
}

void MPool::CombineTuples()
{
    block seeds[PartyNumber];
    NewLabels(&(seeds[MyID]),1);
    void *exsrc[PartyNumber],*exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(seeds[MyID]);
        exdst[i]=&(seeds[i]);
    }
    Exchange(IO,exdst,exsrc,16);
    for(int i=1;i<PartyNumber;i++)
    {
        seeds[0]=_mm_xor_si128(seeds[i],seeds[0]);
    }
    AES_KEY tmpkey;
    AES_set_encrypt_key(seeds[0],&tmpkey);
    block *coefficient;
    coefficient=(block*)_mm_malloc(sizeof(block)*TupleBufferSize*(BucketSize-1),16);
    unsigned char *dy=new unsigned char[PartyNumber*(BucketSize-1)*TupleBufferSize];

    PRG((block*)permutation,BucketSize*TupleBufferSize*sizeof(uint32_t)/sizeof(block),&tmpkey,&Public_Count);
    PRG(coefficient,(BucketSize-1)*TupleBufferSize,&tmpkey,&Public_Count);
    
    block checkresult[4*PartyNumber];
    checkresult[0]=zeroblock;
    for(int i=1;i<2*PartyNumber;i++)
    {
        checkresult[i]=checkresult[0];
    }
    checkresult[2*MyID+2*PartyNumber]=checkresult[0];
    checkresult[2*MyID+2*PartyNumber+1]=checkresult[0];
    
    block tmp[4];
    
    PoolBufferIndex=0;
    for(int i=0;i<BucketSize*TupleBufferSize;i++)
    {
        permutation[i]=permutation[i]%PoolSize;
        if(visited[permutation[i]])
        {
            permutation[i]=PoolBufferIndex+PoolSize;
            PoolBufferIndex++;
        }
        else
        {
            visited[permutation[i]]=true;
        }
    }
    for(int i=0;i<TupleBufferSize;i++)
    {
    dy[(BucketSize-1)*TupleBufferSize*MyID+i*(BucketSize-1)]=extract_bit(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize]+(PartyNumber-1)*2]);
        for(int j=2;j<BucketSize;j++)
        {
            dy[(BucketSize-1)*TupleBufferSize*MyID+i*(BucketSize-1)+j-1]=dy[(BucketSize-1)*TupleBufferSize*MyID+i*(BucketSize-1)]^extract_bit(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+j]+(PartyNumber-1)*2]);
        }
        dy[(BucketSize-1)*TupleBufferSize*MyID+i*(BucketSize-1)]^=extract_bit(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+1]+(PartyNumber-1)*2]);
    }
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(dy[(BucketSize-1)*TupleBufferSize*MyID]);
        exdst[i]=&(dy[(BucketSize-1)*TupleBufferSize*i]);
    }
    Exchange(IO,exdst,exsrc,(BucketSize-1)*TupleBufferSize);
    //begin of check: is y really the claimed y?
    for(int i=0;i<TupleBufferSize;i++)
    {
        for(int k=0;k<PartyNumber;k++)
        {
            if(k<MyID)
            {
                for(int j=1;j<BucketSize;j++)
                {
                    tmp[2]=_mm_xor_si128(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize]+(PartyNumber-1)*2+2*k],Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+j]+(PartyNumber-1)*2+2*k]);
                    mul128(tmp[2],coefficient[i*(BucketSize-1)+j-1],&(tmp[0]),&(tmp[1]));
                    checkresult[2*k]=_mm_xor_si128(checkresult[2*k],tmp[0]);
                    checkresult[2*k+1]=_mm_xor_si128(checkresult[2*k+1],tmp[1]);
                }
            }
            if(k==MyID)
            {
                for(int j=1;j<BucketSize;j++)
                {
                    unsigned tmpdy=0;
                    for(int l=0;l<PartyNumber;l++)
                    {
                        tmpdy^=dy[(BucketSize-1)*TupleBufferSize*l+i*(BucketSize-1)+j-1];
                    }
                    tmpdy^=dy[(BucketSize-1)*TupleBufferSize*MyID+i*(BucketSize-1)+j-1];
                    tmp[2]=_mm_xor_si128(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize]+(PartyNumber-1)*2+1],Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+j]+(PartyNumber-1)*2+1]);
                    
                    for(int l=1;l<PartyNumber-1;l++)
                        tmp[2]=_mm_xor_si128(tmp[2],_mm_xor_si128(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize]+(PartyNumber-1)*2+1+l*2],Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+j]+(PartyNumber-1)*2+1+l*2]));
                    if(tmpdy==1)
                        tmp[2]=_mm_xor_si128(tmp[2],Delta);
                    mul128(tmp[2],coefficient[i*(BucketSize-1)+j-1],&(tmp[0]),&(tmp[1]));
                    checkresult[2*k+2*PartyNumber]=_mm_xor_si128(checkresult[2*k+2*PartyNumber],tmp[0]);
                    checkresult[2*k+1+2*PartyNumber]=_mm_xor_si128(checkresult[2*k+2*PartyNumber+1],tmp[1]);
                }
            }
            if(k>MyID)
            {
                for(int j=1;j<BucketSize;j++)
                {
                    tmp[2]=_mm_xor_si128(Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize]+(PartyNumber-1)*2+2*k-2],Pool[(PartyNumber-1)*2*3*permutation[i*BucketSize+j]+(PartyNumber-1)*2+2*k-2]);
                    mul128(tmp[2],coefficient[i*(BucketSize-1)+j-1],&(tmp[0]),&(tmp[1]));
                    checkresult[2*k]=_mm_xor_si128(checkresult[2*k],tmp[0]);
                    checkresult[2*k+1]=_mm_xor_si128(checkresult[2*k+1],tmp[1]);
                }
            }
            
        }
    }
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(checkresult[2*i]);
        exdst[i]=&(checkresult[2*i+2*PartyNumber]);
    }
    Exchange(IO,exdst,exsrc,32);
    for(int i=1;i<PartyNumber;i++)
    {
        checkresult[2*PartyNumber]=_mm_xor_si128(checkresult[2*PartyNumber],checkresult[2*PartyNumber+2*i]);
        checkresult[2*PartyNumber+1]=_mm_xor_si128(checkresult[2*PartyNumber+1],checkresult[2*PartyNumber+2*i+1]);
    }
    if((_mm_testz_si128(checkresult[2*PartyNumber],all1)!=1)||(_mm_testz_si128(checkresult[2*PartyNumber+1],all1)!=1))
    {
        printf("Combine error\n");
    }
    for(int i=0;i<(BucketSize-1)*TupleBufferSize;i++)
    {
        for(int j=1;j<PartyNumber;j++)
        {
            dy[i]^=dy[i+(BucketSize-1)*TupleBufferSize*j];
        }
    }
    for(int i=0;i<TupleBufferSize;i++)
    {
        memcpy(&(TupleBuffer[6*(PartyNumber-1)*i]),&(Pool[(PartyNumber-1)*6*permutation[i*BucketSize]]),6*(PartyNumber-1)*16);
        for(int j=1;j<BucketSize;j++)
        {
            for(int k=0;k<(PartyNumber-1)*2;k++)
            {
                TupleBuffer[6*(PartyNumber-1)*i+k]=_mm_xor_si128(TupleBuffer[6*(PartyNumber-1)*i+k],Pool[(PartyNumber-1)*6*permutation[i*BucketSize+j]+k]);
            }
            for(int k=0;k<(PartyNumber-1)*2;k++)
            {
                TupleBuffer[6*(PartyNumber-1)*i+4*(PartyNumber-1)+k]=_mm_xor_si128(TupleBuffer[6*(PartyNumber-1)*i+4*(PartyNumber-1)+k],Pool[(PartyNumber-1)*6*permutation[i*BucketSize+j]+4*(PartyNumber-1)+k]);
            }
            if(dy[i*(BucketSize-1)+j-1]==1)
            {
                for(int k=0;k<(PartyNumber-1)*2;k++)
                {
                    TupleBuffer[6*(PartyNumber-1)*i+4*(PartyNumber-1)+k]=_mm_xor_si128(TupleBuffer[6*(PartyNumber-1)*i+4*(PartyNumber-1)+k],Pool[(PartyNumber-1)*6*permutation[i*BucketSize+j]+k]);
                }
            }
        }
    }
    for(int i=0;i<BucketSize*TupleBufferSize;i++)
    {
        if(permutation[i]<PoolSize)
        {
            visited[permutation[i]]=false;
            memcpy(&(Pool[(PartyNumber-1)*2*3*permutation[i]]),
                   &(PoolBuffer[(PartyNumber-1)*2*3*PoolBufferIndex]),
                   (PartyNumber-1)*2*3*16);
            PoolBufferIndex++;
        }
    }
    delete[] dy;
    _mm_free(coefficient);
    NewLeakyTuples(PoolBuffer,TupleBufferSize*BucketSize);
}
