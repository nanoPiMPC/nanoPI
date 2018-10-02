typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;
#define Length 12
#define EDLength 50

Index Mux1 (Index x,Index y,Index c)
{
    return XOR (x,AND (c,XOR (x,y)));
}

void Mux(Index *z,Index *x, Index *y, Index c)
{
    int i;
    for(i=0;i<Length;i++)
        z[i]=Mux1(x[i],y[i],c);
}

Index Compare1 (Index x,Index y,Index c) {
    return Mux1 (c,x,XOR (x,y));
}

Index Compare (Index * x,Index * y) {
    Index t;
    t = AND (XOR (x[0],y[0]),x[0]);
    for (int i = 1; i < Length; i++)
        t = Compare1 (x[i],y[i],t);
    return t;
}

void add (Index *z,Index *x,Index *y)
{
    Index t;
    t = AND (x[0],y[0]);
    z[0] = XOR (x[0],y[0]);
    int i;
    for (i = 1; i < Length; i++)
    {
        z[i] = XOR (t,x[i]);
        t = Mux1 (x[i],y[i],z[i]);
        z[i] = XOR (z[i],y[i]);
    }
}

void add1 (Index *z,Index *x,Index y)
{
    Index t;
    t = AND (x[0],y);
    z[0] = XOR (x[0],y);
    int i;
    for (i = 1; i<Length; i++)
    {
        z[i] = XOR (t,x[i]);
        t = AND (x[i],XOR (z[i],One));
    }
}

void ED(Index *z,Index *x,Index *y)
{
    
/*    Index matrix0[(EDLength+1)*Length];
    Index matrix1[(EDLength+1)*Length];
*/
    Index matrix0[612];
      Index matrix1[612];

    Index a[48];
    int i,j;
    
    for(i=0;i<Length;i++)
    {
        matrix0[i]=__pool__COPY(Zero);
    }
    for(i=1;i<EDLength+1;i++)
    {
        add1(matrix0+i*Length, matrix0+(i-1)*Length,One);
    }
    
    for(i=1;i<EDLength+1;i++)
    {
        add1(matrix1,matrix0,One);
        for(j=1;j<EDLength+1;j++)
        {
            add1(a,&(matrix0[j*Length]),One);
            add1(&(a[Length]),&(matrix1[(j-1)*Length]),One);
            Index tmp1=__pool__XOR(x[2*(i-1)],y[2*(j-1)]);
            Index tmp2=__pool__XOR(x[2*(i-1)+1],y[2*(j-1)+1]);
            Index tmp3=__pool__AND(tmp1,tmp2);
            
            add1(&(a[2*Length]),&(matrix0[(j-1)*Length]),tmp3);
            Index tmp4=Compare(a,&(a[1*Length]));
            Mux(&(a[3*Length]),a,&(a[1*Length]),tmp4);
            Index tmp5=Compare(&(a[3*Length]),&(a[2*Length]));
            Mux(&(matrix1[j*Length]),&(a[3*Length]),&(a[2*Length]),tmp5);
            for(int k=0;k<Length;k++)
            {
                matrix0[(j-1)*Length+k]=matrix1[(j-1)*Length+k];
            }
        }
        for(int k=0;k<Length;k++)
        {
            matrix0[EDLength*Length+k]=matrix1[EDLength*Length+k];
        }
    }
    for(i=0;i<Length;i++)
        z[i]=__pool__COPY(matrix0[EDLength+i]);
}

