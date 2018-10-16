#define Length 8
typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;
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
    int i;
    t = AND (XOR (x[0],y[0]),x[0]);
    for (i = 1; i < Length; i++)
        t = Compare1 (x[i],y[i],t);
    return t;
}
void Swap(Index *In1,Index *In2,Index c)
{
    Index tmp[Length],tmp1[Length];
    Mux(tmp,In1,In2,c);
    int i;
    for(i=0;i<Length;i++)
    {
        tmp1[i]=XOR(tmp[i],In1[i]);
        In2[i]=XOR(tmp1[i],In2[i]);
        In1[i]=tmp[i];
    }
}
void SortCompare(Index Sign,Index *In,int len)
{
    int dist=len/2;
    Index tmp;
    int i;
    for(i=0;i<dist;i++)
    {
        tmp=Compare(&(In[Length*i]),&(In[Length*i+dist]));
        tmp=XOR(Sign,tmp);
        Swap(&(In[i*Length]),&(In[(i+dist)*Length]),tmp);
    }
}
void SortMerge(Index Sign, Index *In, int len)
{
    if (len==1) return;
    SortCompare(Sign, In, len);
    SortMerge(Sign,In,len/2);
    SortMerge(Sign,&(In[Length*len/2]),len/2);
}
void Sort(Index Sign,Index *In, int len)
{
    if (len<=1) return;
    Sort(One,In,len/2);
    Sort(Zero,In+Length*len/2,len/2);
    SortMerge(Sign,In,len);
}
