#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

double alpha, beta;
char inputString[256];

    printf("%s", "Введите угол альфа в градусах: ");
    scanf("%s", inputString);
    alpha = strtod(inputString, NULL);

    printf("%s", "Введите угол бета в градусах: ");
    scanf("%s", inputString);
    beta = strtod(inputString, NULL);

    alpha = M_PI * (alpha / 180); beta = M_PI * (beta / 180);

    printf("z1 = %f \n", pow((cos(alpha)-cos(beta)), 2.0)-pow((sin(alpha)-sin(beta)), 2.0));
    printf("z2 = %f \n", -4.0*pow(sin((alpha-beta)/2.0), 2.0)*cos(alpha+beta));
    return 0;
}
