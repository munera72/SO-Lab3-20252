#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

//   Función para medir tiempo
double GetTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

double CalcPi(int n);

int main(int argc, char **argv)
{
    int n = 2000000000;
    const double fPi25DT = 3.141592653589793238462643;
    double fPi;
    double fTimeStart, fTimeEnd;

#ifdef READ_INPUT  
    printf("Enter the number of intervals: ");
    scanf("%d",&n);
#endif

    if (n <= 0 || n > 2147483647 )
    {
        printf("\nGiven value has to be between 0 and 2147483647\n");
        return 1;
    }

    fTimeStart = GetTime();

    fPi = CalcPi(n);

    fTimeEnd = GetTime();

    printf("\npi is approximately = %.20f \nError               = %.20f\n",
           fPi, fabs(fPi - fPi25DT));

    printf("Tiempo = %f segundos\n", fTimeEnd - fTimeStart);

    return 0;
}

double f(double a)
{
    return (4.0 / (1.0 + a*a));
}

double CalcPi(int n)
{
    const double fH   = 1.0 / (double) n;
    double fSum = 0.0;
    double fX;
    int i;

    for (i = 0; i < n; i += 1)
    {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }
    return fH * fSum;
}
