#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct racer
{
    char name[10];
}RACER;
typedef struct country
{
    char name[10];
    RACER *racer;
}COUNTRY;


int countriesCount = 0;

void merge(int leftSize, COUNTRY *leftArray, int rightSize, COUNTRY *rightArray, COUNTRY *result)
{
    int left = 0, right = 0;

    for (int i = 0; i < leftSize+rightSize; i++)
    {
        //printf("%s\n%s\n", leftArray[left].name, rightArray[right].name);
        if ((left < leftSize) && (right < rightSize))
        {
            if (strcmp(leftArray[left].name, rightArray[right].name) <= 0)
            {
                result[i] = leftArray[left];
                left++;
                //printf("-%s\n", leftArray[left].name);
            }
            else{
                result[i] = rightArray[right];
                right++;
                //printf("-%s\n", rightArray[right].name);
            }
        }
        else if (left == leftSize)
        {
            result[i] = rightArray[right];
            right++;
            //printf("-%s\n", rightArray[right].name);
        }
        else if (right == rightSize)
        {
            result[i] = leftArray[left];
            left++;
            //printf("-%s\n", leftArray[left].name);
        }
        //printf("---\n");
    }
}

void mergeSort(int size, COUNTRY *array)
{
    if (size == 1) { return; }

    int divideIndex = size/2;
    COUNTRY *leftArray = (COUNTRY *)malloc(divideIndex*sizeof(COUNTRY)),
    *rightArray = (COUNTRY *)malloc((size-divideIndex)*sizeof(COUNTRY));

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

void randomData()
{
    FILE *data = fopen("data.txt", "w");
    fprintf(data, "%d\n", 100000);
    for (int i = 0; i < 100000; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            fprintf(data, "%d ", rand()%100000);
        }
        fprintf(data, "\n");
    }
}

int main()
{
    //clock_t begin = clock();

    FILE *inputFile = fopen("race.in", "r");
    int racerAmount; fscanf(inputFile, "%d", &racerAmount);
    COUNTRY countries[100000];

    for (int i = 0; i < racerAmount; i++)
    {
        char countryName[10]; fscanf(inputFile, "%s", countryName);
        char racerName[10]; fscanf(inputFile, "%s", racerName);

        RACER *racer = malloc(sizeof(RACER));
        strcpy(racer->name, racerName);

        countries[i].racer = racer;
        strcpy(countries[i].name, countryName);

        countriesCount++;
    }
    fclose(inputFile);

    mergeSort(countriesCount, countries);

    FILE *outputFile = fopen("race.out", "w");
    for (int countryIndex = 0; countryIndex < countriesCount; countryIndex++)
    {
        if (countryIndex == 0 || strcmp(countries[countryIndex].name, countries[countryIndex-1].name) != 0)
        {
            fprintf(outputFile, "=== %s ===\n", countries[countryIndex].name);
        }
        fprintf(outputFile, "%s\n", countries[countryIndex].racer->name);
    }

    /*clock_t end = clock();
    printf("%f\n", (float)(end-begin)/CLOCKS_PER_SEC);
    printf("%d", countriesCount);*/
    return 0;
}