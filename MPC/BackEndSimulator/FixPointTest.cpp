//
//  FixPointTest.cpp
//  
//
//  Created by Sourgroup on 4/29/18.
//

#include "FixPoint.hpp"
void FixPointTest()
{
    double x=1.375,y=3.15;
    __pool__fixpoint f1,f2,f3;
    __pool__make__fixpoint(&f1,x);
    printf("%f\n",reveal(&f1));
    __pool__make__fixpoint(&f2,y);
    printf("%f\n",reveal(&f2));
    __pool__init__fixpoint(&f3);
    __pool__fixpoint__mul(&f3,&f1,&f2);
    printf("%f\n",reveal(&f3));
    __pool__RELEASE__fixpoint(&f3);
    __pool__bool b;
    __pool__init__bool(&b);
    __pool__fixpoint__lt(&b,&f2,&f1);
    printf("%d\n",Map.Read(b.bit)->value);
    return;
}
