//
// Created by Георгий Круглов on 18.12.2020.
//

#ifndef LAB14_EXPANSION_H
#define LAB14_EXPANSION_H

typedef enum {
    leading,
    trailing,
    top,
    bottom
}DIRECTION;

void **expand(void **array, int *rowCount, int *rowLength, int blockSize, DIRECTION direction, void *defaultValue) {
    if (direction == top || direction == bottom)
        (*rowCount)++;
    else
        (*rowLength)++;

    void **newArray = calloc(*rowCount, sizeof(void *));
    for (int i = 0; i < *rowCount; i++) {
        newArray[i] = calloc(*rowLength, blockSize);
    }

    if (direction == top) {
        for (int j = 0; j < *rowLength; j++)
            memcpy(&newArray[0][j * blockSize], defaultValue, blockSize);
        for (int i = 1; i < *rowCount; i++) {
            for (int j = 0; j < *rowLength; j++) {
                memcpy(&newArray[i][j * blockSize], &array[i - 1][j * blockSize], blockSize);
            }
        }

        for (int i = 0; i < *rowCount - 1; i++) {
            free(array[i]);
        }
        free(array);

        return newArray;
    }
    if (direction == bottom) {
        for (int j = 0; j < *rowLength; j++)
            memcpy(&newArray[*rowCount - 1][j * blockSize], defaultValue, blockSize);
        for (int i = 0; i < *rowCount - 1; i++) {
            for (int j = 0; j < *rowLength; j++) {
                memcpy(&newArray[i][j * blockSize], &array[i][j * blockSize], blockSize);
            }
        }

        for (int i = 0; i < *rowCount - 1; i++) {
            free(array[i]);
        }
        free(array);

        return newArray;
    }

    if (direction == leading) {
        for (int i = 0; i < *rowCount; i++)
            memcpy(newArray[i], defaultValue, blockSize);
        for (int i = 0; i < *rowCount; i++) {
            for (int j = 1; j < *rowLength; j++) {
                memcpy(&newArray[i][j * blockSize], &array[i][(j - 1) * blockSize], blockSize);
            }
        }

        for (int i = 0; i < *rowCount; i++) {
            free(array[i]);
        }
        free(array);

        return newArray;
    }
    if (direction == trailing) {
        for (int i = 0; i < *rowCount; i++)
            memcpy(&newArray[i][(*rowLength - 1) * blockSize], defaultValue, blockSize);
        for (int i = 0; i < *rowCount; i++) {
            for (int j = 0; j < *rowLength - 1; j++) {
                memcpy(&newArray[i][j * blockSize], &array[i][j * blockSize], blockSize);
            }
        }

        for (int i = 0; i < *rowCount; i++) {
            free(array[i]);
        }
        free(array);

        return newArray;
    }

    printf("\n-----------\nArray expansion not succeeded\n-----------\n");

    return array;
}

#endif //LAB14_EXPANSION_H
