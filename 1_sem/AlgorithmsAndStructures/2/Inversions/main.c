#include <stdio.h>
#include <stdlib.h>

long int inversionsCount = 0;

void compare(long int leftSize, long int const *leftArray, long int rightSize, long int const *rightArray, long int *result)
{
    long int left = 0, right = 0;
    for (long int i = 0; i < leftSize+rightSize; i++)
    {
        if (left < leftSize && right < rightSize)
        {
            if (leftArray[left] > rightArray[right])
            {
                result[i] = rightArray[right];
                inversionsCount += leftSize-left;
                right++;
            }
            else
            {
                result[i] = leftArray[left];
                left++;
            }
        }
        else if (left == leftSize)
        {
            result[i] = rightArray[right];
            right++;
        }
        else if (right == rightSize)
        {
            result[i] = leftArray[left];
            left++;
        }
    }
}

void divideCompare(long int size, long int *array)
{
    if (size == 1) { return; }

    long int divideIndex = size/2;
    long int *leftArray = malloc(divideIndex*sizeof(long int)), *rightArray = malloc((size-divideIndex)*sizeof(long int));

    for (long int i = 0; i < divideIndex; i++)
    {
        leftArray[i] = array[i];
    }
    for (long int i = divideIndex; i < size; i++)
    {
        rightArray[i-divideIndex] = array[i];
    }

    divideCompare(divideIndex, leftArray);
    divideCompare(size-divideIndex, rightArray);

    compare(divideIndex, leftArray, size-divideIndex, rightArray, array);
}

int main() {
    FILE *inputFile = fopen("inversions.in", "r");
    long int amount; fscanf(inputFile, "%li", &amount);
    long int *array = malloc(amount*sizeof(long int));

    for (long int i = 0; i < amount; i++)
    {
        fscanf(inputFile, "%li", array+i);
    }
    fclose(inputFile);

    /*long int *array = malloc((long int)1e5 * sizeof(long int));
    int j = 0;

    for (long int i = (long int)1e5; i > 0; i--)
    {
        array[j] = i;
        j++;
    }*/

    divideCompare(amount, array);

    FILE *outputFile = fopen("inversions.out", "w");
    fprintf(outputFile, "%li", inversionsCount);
    fclose(outputFile);
    return 0;
}
