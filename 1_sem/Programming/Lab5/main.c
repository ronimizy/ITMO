#include <stdio.h>

int main()
{
int array[7] = {123, 123, 123, 123, 456, 321, 1},
    matrixA[2][2] = {1, 2, 3, 4},
    matrixB[2][2] = {1, 0, 0, 1},
    matrixC[2][2] = {0, 0, 0, 0};


    printf("[");
    for (int i = 0; i < 5; i++)
    {
        printf("%d", array[i]);
        i == 4 ? printf("] \n") : printf(", ");
    }

    for (int line = 0; line < 2; line++)
    {
        for (int column = 0; column < 2; column++)
        {
            for (int offset = 0; offset < 2; offset++)
            {
                matrixC[line][column] += matrixA[offset][column] * matrixB[line][offset];
            }
        }
    }

    return 0;
}