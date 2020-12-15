#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

char inputString[256], answers[2][256];
int number;
unsigned theBit = 1 << 9;
strcpy(answers[1], "Число входит в заданный диапазон значений");
strcpy(answers[0], "Число не входит в заданный диапазон значений");

    printf("Введите число: ");
    scanf("%s", inputString);
    number = (int)strtol(inputString, NULL, 10);
    printf("%s \n", answers[(number >= -100) && (number <= 100)]);

    printf("Введите слудующее число в 10-тичной СС: ");
    scanf("%s", inputString);
    number = (int)strtol(inputString, NULL, 10);
    printf("%d", ((unsigned)number & theBit) == theBit);

    return 0;
}