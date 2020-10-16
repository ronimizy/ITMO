#include <stdio.h>

void merge(int leftSize, int const leftArray[leftSize], int rightSize, int const rightArray[rightSize], int result[leftSize+rightSize])
{
    int left = 0, right = 0;

    for (int i = 0; i < leftSize+rightSize; i++)
    {
        if ((left < leftSize) && (right < rightSize))
        {
            if (leftArray[left] <= rightArray[right])
            {
                result[i] = leftArray[left];
                left++;
            }
            else{
                result[i] = rightArray[right];
                right++;
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

void mergeSort(int size, int *array)
{
    if (size == 1) { return; }
    int divideIndex = size/2;
    int leftArray[divideIndex], rightArray[size-divideIndex];

    for (int i = 0; i < divideIndex; i++)
    {
        leftArray[i] = array[i];
    }
    for (int i = divideIndex; i < size; i++)
    {
        rightArray[i-divideIndex] = array[i];
    }

    mergeSort(divideIndex, leftArray);
    mergeSort(size-divideIndex, rightArray);

    merge(divideIndex, leftArray, size-divideIndex, rightArray, array);
}

int main()
{
FILE *inputFile = fopen("sort.in", "r"), *outputFile = fopen("sort.out", "w");
int arraySize; fscanf(inputFile, "%d", &arraySize);
int array[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        fscanf(inputFile, "%i", &array[i]);
    }
    fclose(inputFile);

    mergeSort(arraySize, array);

    for (int i = 0; i < arraySize; i++)
    {
        fprintf(outputFile, "%i ", array[i]);
    }



    return 0;
}