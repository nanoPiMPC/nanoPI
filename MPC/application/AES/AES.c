typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;

void GFINV(bit src[])
{
    bit T[27],M[63],L[30];
    T[0]=XOR(src[0],src[3]);
    T[1]=XOR(src[0],src[5]);
    T[2]=XOR(src[0],src[6]);
    T[3]=XOR(src[3],src[5]);
    T[4]=XOR(src[4],src[6]);
    T[5]=XOR(T[0],T[4]);
    T[6]=XOR(src[1],src[2]);
    T[7]=XOR(src[7],T[5]);
    T[8]=XOR(src[7],T[6]);
    T[9]=XOR(T[5],T[6]);
    T[10]=XOR(src[1],src[5]);
    T[11]=XOR(src[2],src[5]);
    T[12]=XOR(T[2],T[3]);
    T[13]=XOR(T[5],T[10]);
    T[14]=XOR(T[4],T[10]);
    T[15]=XOR(T[4],T[11]);
    T[16]=XOR(T[8],T[15]);
    T[17]=XOR(src[3],src[7]);
    T[18]=XOR(T[6],T[17]);
    T[19]=XOR(T[0],T[18]);
    T[20]=XOR(src[6],src[7]);
    T[21]=XOR(T[6],T[20]);
    T[22]=XOR(T[1],T[21]);
    T[23]=XOR(T[1],T[9]);
    T[24]=XOR(T[19],T[16]);
    T[25]=XOR(T[2],T[15]);
    T[26]=XOR(T[0],T[11]);
    
    M[0]=AND(T[5],T[12]);
    M[1]=AND(T[7],T[22]);
    M[3]=AND(src[7],T[18]);
    M[5]=AND(T[2],T[15]);
    M[6]=AND(T[8],T[21]);
    M[8]=AND(T[16],T[19]);
    M[10]=AND(T[0],T[14]);
    M[11]=AND(T[3],T[26]);
    M[13]=AND(T[1],T[9]);
    
    M[2]=T[13];
    M[7]=T[24];
    M[45]=T[5];
    M[46]=T[7];
    M[47]=src[7];
    M[48]=T[14];
    M[49]=T[8];
    M[50]=T[16];
    M[51]=T[14];
    M[52]=T[26];
    M[53]=T[9];
    M[54]=T[12];
    M[55]=T[22];
    M[56]=T[18];
    M[57]=T[2];
    M[58]=T[21];
    M[59]=T[19];
    M[60]=T[0];
    
    M[61]=T[3];
    M[62]=T[1];
    M[2]=XOR(M[2],M[0]);
    M[4]=XOR(M[3],M[0]);
    M[7]=XOR(M[7],M[5]);
    M[9]=XOR(M[8],M[5]);
    M[12]=XOR(M[10],M[11]);
    M[14]=XOR(M[10],M[13]);
    M[15]=XOR(M[2],M[1]);
    M[16]=XOR(M[4],M[15]);
    M[17]=XOR(M[6],M[7]);
    M[18]=XOR(M[9],M[14]);
    M[19]=XOR(M[15],M[12]);
    M[20]=XOR(M[16],M[14]);
    M[21]=XOR(M[12],M[17]);
    M[22]=XOR(M[18],M[21]);
    M[23]=XOR(M[21],M[22]);
    M[26]=XOR(M[19],M[20]);
    M[24]=AND(M[19],M[21]);
    M[30]=AND(M[19],M[22]);
    M[33]=AND(M[20],M[21]);
    M[25]=XOR(M[20],M[24]);
    M[27]=XOR(M[22],M[24]);
    M[32]=XOR(M[26],M[24]);
    M[35]=XOR(M[23],M[24]);
    M[28]=AND(M[26],M[27]);
    M[29]=AND(M[23],M[25]);
    M[31]=AND(M[26],M[30]);
    M[34]=AND(M[23],M[33]);
    
    M[36]=XOR(M[20],M[28]);
    M[37]=XOR(M[31],M[32]);
    M[38]=XOR(M[22],M[29]);
    M[39]=XOR(M[34],M[35]);
    M[40]=XOR(M[37],M[39]);
    M[41]=XOR(M[36],M[38]);
    M[42]=XOR(M[36],M[37]);
    M[43]=XOR(M[38],M[39]);
    M[44]=XOR(M[41],M[30]);
    
    M[45]=AND(M[45],M[43]);
    M[46]=AND(M[46],M[39]);
    M[47]=AND(M[47],M[38]);
    M[48]=AND(M[48],M[42]);
    M[49]=AND(M[49],M[37]);
    M[50]=AND(M[50],M[36]);
    M[51]=AND(M[51],M[41]);
    M[52]=AND(M[52],M[44]);
    M[53]=AND(M[53],M[40]);
    M[54]=AND(M[54],M[43]);
    M[55]=AND(M[55],M[39]);
    M[56]=AND(M[56],M[38]);
    M[57]=AND(M[57],M[42]);
    M[58]=AND(M[58],M[37]);
    M[59]=AND(M[59],M[36]);
    M[60]=AND(M[60],M[41]);
    M[61]=AND(M[61],M[44]);
    M[62]=AND(M[62],M[40]);
    L[0]=XOR(M[60],M[61]);
    L[1]=XOR(M[49],M[55]);
    L[2]=XOR(M[45],M[47]);
    L[3]=XOR(M[46],M[54]);
    L[4]=XOR(M[53],M[57]);
    L[5]=XOR(M[48],M[60]);
    L[6]=XOR(M[61],L[5]);
    L[7]=XOR(M[45],L[3]);
    L[8]=XOR(M[50],M[58]);
    L[9]=XOR(M[51],M[52]);
    L[10]=XOR(M[52],L[4]);
    L[11]=XOR(M[59],L[2]);
    L[12]=XOR(M[47],M[50]);
    L[13]=XOR(M[49],L[0]);
    L[14]=XOR(M[51],M[60]);
    L[15]=XOR(M[54],L[1]);
    L[16]=XOR(M[55],L[0]);
    L[17]=XOR(M[56],L[1]);
    L[18]=XOR(M[57],L[8]);
    L[19]=XOR(M[62],L[4]);
    L[20]=XOR(L[0],L[1]);
    L[21]=XOR(L[1],L[7]);
    L[22]=XOR(L[3],L[12]);
    L[23]=XOR(L[18],L[2]);
    L[24]=XOR(L[15],L[9]);
    L[25]=XOR(L[6],L[10]);
    L[26]=XOR(L[7],L[9]);
    L[27]=XOR(L[8],L[10]);
    L[28]=XOR(L[11],L[14]);
    L[29]=XOR(L[11],L[17]);
    src[0]=XOR(L[6],L[24]);
    src[1]=XOR(L[16],L[26]);
    src[2]=XOR(L[19],L[28]);
    src[3]=XOR(L[6],L[21]);
    src[4]=XOR(L[20],L[22]);
    src[5]=XOR(L[25],L[29]);
    src[6]=XOR(L[13],L[27]);
    src[7]=XOR(L[6],L[23]);
}
void ShiftRows(bit src[])
{
    bit dst[128];
    int i,j,k;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            for(k=0;k<8;k++)
            {
                dst[i*32+j*8+k]=src[i*32+((j+i)%4)*8+k];
            }
        }
    }
    for(int i=0;i<128;i++)
        src[i]=dst[i];
}
void MixColumn(bit src[])
{
    bit dst[128];
    int c,i,j;
    bit a02s[32];
    for(c=0;c<4;c++)
    {
        for(i=0;i<4;i++)
        {
            a02s[i*8+4]=XOR(src[c*8+i*32+7],src[c*8+i*32+3]);
            a02s[i*8+3]=XOR(src[c*8+i*32+7],src[c*8+i*32+2]);
            a02s[i*8+1]=XOR(src[c*8+i*32+7],src[c*8+i*32+0]);
        }
        
        i=0;
        {
            dst[c*8+i]=XOR(src[c*8+7],src[c*8+7+32]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+64]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+96]);
            
            dst[c*8+i+32]=XOR(src[c*8+7+64],src[c*8+7+32]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i+96]);
            
            dst[c*8+i+64]=XOR(src[c*8+7+64],src[c*8+7+96]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i+16]);
            
            dst[c*8+i+96]=XOR(src[c*8+7+96],src[c*8+7]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+32]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+64]);
        }
        
        i=2;
        {
            dst[c*8+i]=XOR(src[c*8+1],src[c*8+1+32]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+64]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+96]);
            
            dst[c*8+i+32]=XOR(src[c*8+1+64],src[c*8+1+32]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i+96]);
            
            dst[c*8+i+64]=XOR(src[c*8+1+64],src[c*8+1+96]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i+16]);
            
            dst[c*8+i+96]=XOR(src[c*8+1+96],src[c*8+1]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+32]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+64]);
        }
        
        for(i=5;i<8;i++)
        {
            dst[c*8+i]=XOR(src[c*8-1+i],src[c*8-1+32+i]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+64]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+96]);
            
            dst[c*8+i+32]=XOR(src[c*8-1+i+64],src[c*8-1+32+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i+96]);
            
            dst[c*8+i+64]=XOR(src[c*8-1+i+64],src[c*8-1+96+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i+16]);
            
            dst[c*8+i+96]=XOR(src[c*8-1+i+96],src[c*8-1+i]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+32]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+64]);
        }
        i=1;
        {
            dst[c*8+i]=XOR(a02s[i],a02s[1*8+i]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+64]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+96]);
            
            dst[c*8+i+32]=XOR(a02s[2*8+i],a02s[1*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i+96]);
            
            dst[c*8+i+64]=XOR(a02s[2*8+i],a02s[3*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i+16]);
            
            dst[c*8+i+96]=XOR(a02s[3*8+i],a02s[0*8+i]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+32]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+64]);
        }
        for(i=3;i<=4;i++)
        {
            dst[c*8+i]=XOR(a02s[0*8+i],a02s[1*8+i]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+64]);
            dst[c*8+i]=XOR(dst[c*8+i],src[c*8+i+96]);
            
            dst[c*8+i+32]=XOR(a02s[2*8+i],a02s[1*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i]);
            dst[c*8+i+32]=XOR(dst[c*8+i+32],src[c*8+i+96]);
            
            dst[c*8+i+64]=XOR(a02s[2*8+i],a02s[3*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i]);
            dst[c*8+i+64]=XOR(dst[c*8+i+64],src[c*8+i+16]);
            
            dst[c*8+i+96]=XOR(a02s[3*8+i],a02s[0*8+i]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+32]);
            dst[c*8+i+96]=XOR(dst[c*8+i+96],src[c*8+i+64]);
        }
    }
    for(int i=0;i<128;i++)
        src[i]=dst[i];
}
void RotWord(bit a[])
{
    bit tmp;
    int i,j;
    for(i=0;i<8;i++)
    {
        tmp=a[i];
        for(j=0;j<3;j++)
            a[j*8+i]=a[j*8+i+8];
        a[24+i]=tmp;
    }
}
void Mul2(bit b[])
{
    bit tmp;
    tmp=b[7];
    b[7]=b[6];
    b[6]=b[5];
    b[5]=b[4];
    b[4]=XOR(b[3],tmp);
    b[3]=XOR(b[2],tmp);
    b[2]=b[1];
    b[1]=XOR(b[0],tmp);
    b[0]=tmp;
}
void KEYEXPENSION(bit AESROUNDKEY[],bit AESKEY[])
{
    bit Rcon[8];
    bit tmp[32];
    bit tmps[8];
    int i,j;
    for(i=0;i<8;i++)
        Rcon[i]=Zero;
    Rcon[1]=One;
    for(i=0;i<128;i++)
        AESROUNDKEY[i]=AESKEY[i];
    for(i=4;i<44;i++)
    {
        for(j=0;j<32;j++)
            tmp[j]=AESROUNDKEY[(i-1)*32+j];
        if(i%4==0)
        {
            RotWord(tmp);
            for(j=0;j<4;j++)
            {
                GFINV(&(tmp[8*j]));
            }
            for(j=0;j<8;j++)
                tmp[j]=XOR(tmp[j],Rcon[j]);
            Mul2(Rcon);
        }
        for(j=0;j<32;j++)
            AESROUNDKEY[i*32+j]=XOR(AESROUNDKEY[i*32+j-128],tmp[j]);
    }
}
void AddRoundKey(Index ROUNDKEY[],Index MSG[],int round)
{
    int i;
    for(i=0;i<128;i++)
    {
        MSG[i]=XOR(MSG[i],ROUNDKEY[128*round+i]);
    }
}
void AES(bit *input)
{
    int i;
    bit AESROUNDKEY[1408];
    KEYEXPENSION(AESROUNDKEY,&(input[128]));
    for(i=1;i<10;i++)
    {
        SubBytes(input);
        ShiftRows(input);
        MixColumn(input);
        AddRoundKey(AESROUNDKEY,input,i);
    }
    SubBytes(input);
    ShiftRows(input);
    AddRoundKey(AESROUNDKEY,input,i);
}

