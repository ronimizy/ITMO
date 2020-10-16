#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array, buffer = 0, j = 0, step = sizeof(int);

    array = (int*)malloc(4*step);

    for (int i = -1; i > -5; i--)
    {
        buffer = buffer*10 + i;
        array[j] = buffer;
        j++;
    }

    printf("array = [");
    for (int i = 0; i < 4; i++)
    {
        printf("%d", *(array+i));
        i != 3 ? printf(", ") : printf("]\n");
    }

    free(array);
}