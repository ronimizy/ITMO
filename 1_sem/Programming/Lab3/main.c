#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
char inputString[256] = "";
unsigned number1, number2;

    printf("Введите число в 16-тиричной СС: ");
    scanf("%s", inputString);
    number1 = strtoul(inputString, NULL, 16);

    printf("%o \n", number1); //Task2 - translate to 8
    printf("%o \n", number1 << 1); //Task3 - 1 bit left shift
    printf("%o \n", ~number1); //Task4 - bit reverse

    printf("Введите число в 8-ричной СС: ");
    scanf("%s", inputString);
    number2 = strtoul(inputString, NULL, 8);

    printf("%o", number1 & number2); //Task5 - &

    return 0;
}
