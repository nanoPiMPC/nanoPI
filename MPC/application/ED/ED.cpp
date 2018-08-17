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

void add1 (Index *z,Index *x,Index y)//add an Length-Index number by a 1-Index
{
    Index t;
    t = AND (x[0],y);
    z[0] = XOR (x[0],y);
    int i;
    for (i = 1; i<Length; i++)
    {
        z[i] = XOR (t,x[i]);
        t = AND (x[i],XOR (z[i],one));
    }
}

void ED(Index *z,Index *x,Index *y)
{
    Index matrix[EDLength+1][EDLength+1][Length];
    Index a[4][Length];
    int i,j;
    for(i=0;i<Length;i++)
        matrix[0][0][i]=zero;
    for(i=1;i<EDLength+1;i++)
    {
        add1(matrix[i][0],matrix[i-1][0],one);
        add1(matrix[0][i],matrix[i-1][0],one);
    }
    for(i=1;i<EDLength+1;i++)
    {
        for(j=1;j<EDLength+1;j++)
        {
            add1(a[0],matrix[i-1][j],one);
            add1(a[1],matrix[i][j-1],one);
            add1(a[2],matrix[i-1][j-1],XOR(x[i-1],y[j-1]));
            Mux(a[3],a[0],a[1],Compare(a[0],a[1]));
            Mux(matrix[i][j],a[3],a[2],Compare(a[3],a[2]));
        }
    }
    for(i=0;i<Length;i++)
        z[i]=matrix[EDLength][EDLength][i];
}

