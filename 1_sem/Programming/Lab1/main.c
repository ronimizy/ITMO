#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main()
{
char inputString[256], *residue;
int number;

    scanf("%s", inputString);
    number = (int)strtol(inputString, &residue, 10);

    if (strcmp(inputString, residue) == 0)
    {
        printf("%s", inputString);
    }
    else
    {
        printf("%d", number);
    }

    return 0;
}
