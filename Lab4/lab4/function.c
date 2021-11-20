#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

double series(double x, double eps)
{
    if(x<eps && x>-eps)
    {
        printf("--------+--------\n");
        printf("—лагаемое обращаетс€ в бесконечность в точке x = 0");
        printf("\n+---------------+\n");
        return 0;
    }
    double a=(1/(3*x)), n=2, res=a;

    do
    {
        if(fabs(a*(1/(4*n*n*x+2*n*x)))<eps)
        {
            break;
        }
        a = a*(1/(4*n*n*x+2*n*x));
        res =  res+a;
        n = n+1;
    }
    while(fabs(a) > eps);

    return res;
}
