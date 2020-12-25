//
// Created by Георгий Круглов on 04.12.2020.
//

#ifndef LAB15_ENCODINGDECODING_H
#define LAB15_ENCODINGDECODING_H

#include <stdio.h>

typedef unsigned long long ULL;
typedef unsigned char UC;

typedef struct Node {
    ULL frequency;
    UC character;
    struct Node *left, *right;
} NODE;


void merge(ULL leftSize, NODE *leftArray[leftSize], ULL rightSize, NODE *rightArray[rightSize],
           NODE *result[leftSize + rightSize]) {
    ULL left = 0, right = 0;

    for (ULL i = 0; i < leftSize + rightSize; i++) {
        if ((left < leftSize) && (right < rightSize)) {
            if (leftArray[left]->frequency >= rightArray[right]->frequency) {
                result[i] = leftArray[left];
                left++;
            } else {
                result[i] = rightArray[right];
                right++;
            }
        } else if (left == leftSize) {
            result[i] = rightArray[right];
            right++;
        } else if (right == rightSize) {
            result[i] = leftArray[left];
            left++;
        }
    }
}

void mergeSort(NODE **array, ULL size) {
    if (size == 1) return;
    ULL divideIndex = size / 2;
    NODE *leftArray[divideIndex], *rightArray[size - divideIndex];

    for (ULL i = 0; i < divideIndex; i++) {
        leftArray[i] = array[i];
    }

    for (ULL i = divideIndex; i < size; i++) {
        rightArray[i - divideIndex] = array[i];
    }

    mergeSort(leftArray, divideIndex);
    mergeSort(rightArray, size - divideIndex);

    merge(divideIndex, leftArray, size - divideIndex, rightArray, array);
}


ULL backwards(ULL value) {
    ULL buffer = 0;

    for (ULL i = 0; i < 8; i++) {
        buffer = buffer * 2 + value % 2;
        value /= 2;
    }

    return buffer;
}

void recover(ULL num, UC *string, ULL start, ULL end) {
    for (ULL i = 0; i < end; i++) {
        string[start + end - 1 - i] = num % 2 + '0';
        num /= 2;
    }

    string[start + end] = '\0';
}

NODE *connectNodes(NODE *left, NODE *right) {
    NODE *n = malloc(sizeof(NODE));

    n->right = right;
    n->left = left;

    n->frequency = right->frequency + left->frequency;
    n->character = -1;

    return n;
}

UC **dictionary;

void code(NODE *n, UC *string, ULL size) {
    if (n->right == NULL) {
        strcpy((char *) dictionary[(ULL) n->character], (const char *) string);
        return;
    }

    string[size + 1] = '\0';
    string[size] = '1';
    code(n->right, string, size + 1);

    string[size + 1] = '\0';
    string[size] = '0';
    code(n->left, string, size + 1);
}

void encode(UC *inputFileName) {
    FILE *inputFile = fopen((const char *) inputFileName, "rb");
    FILE *outputFile = fopen("._______________", "wb");

    dictionary = calloc(256, sizeof(UC *));
    ULL *frequency = calloc(256, sizeof(ULL));

    for (ULL i = 0; i < 256; i++) {
        dictionary[i] = calloc(256, sizeof(UC));
        frequency[i] = 0;
        strcpy((char *) dictionary[i], "");
    }

    int c;
    ULL k = 0;

    NODE **tree = calloc(256, sizeof(NODE *));

    while ((c = getc(inputFile)) != EOF)
        frequency[(UC) c]++;

    for (ULL i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            NODE *n = malloc(sizeof(NODE));

            n->character = (UC) i;
            n->frequency = frequency[i];

            n->right = NULL;
            tree[k++] = n;
        }
    }

    ULL letterCount = k;
    mergeSort(tree, k);

    while (k != 1) {
        mergeSort(tree, k);
        tree[k - 2] = connectNodes(tree[k - 2], tree[k - 1]);
        k--;
    }

    UC *string = calloc(256, sizeof(UC));
    ULL size = 0;

    code(tree[0], string, size);

    fseek(inputFile, 0, SEEK_SET);

    putc((int) letterCount - 1, outputFile);

    for (int i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            ULL count = 0;
            UC n = (UC) strlen((const char *) dictionary[i]), t = 0;

            putc(i, outputFile);
            putc(n, outputFile);

            for (ULL j = 0; j < n; j++) {
                t = t * 2 + (dictionary[i][j] == '0' ? 0 : 1);
                count++;

                if (count == 8) {
                    count = 0;
                    putc(t, outputFile);
                    t = 0;
                }
            }
            if (count != 0) {
                putc(t, outputFile);
            }
        }
    }

    ULL sum = 0, count = 0;
    while ((c = getc(inputFile)) != EOF) {
        for (ULL i = 0; dictionary[c][i] != '\0'; i++) {
            sum = sum * 2 + (dictionary[c][i] - '0');
            count++;

            if (count == 8) {
                putc((UC) sum, outputFile);
                count = 0;
                sum = 0;
            }
        }
    }

    if (count != 0) {
        putc((UC) sum << (8 - count), outputFile);
    }

    putc(8 - (int) count, outputFile);


    for (ULL i = 0; i < 256; i++)
        free(dictionary[i]);
    free(dictionary);
    fclose(inputFile);
    fclose(outputFile);

    remove((const char *) inputFileName);
    rename("._______________", (const char *) inputFileName);
}

void decode(UC *archiveName) {
    FILE *archive = fopen((const char *) archiveName, "rb");
    FILE *decodedFile = fopen("._______________", "wb");

    dictionary = (UC **) malloc(256 * sizeof(UC *));
    for (ULL i = 0; i < 256; i++)
        dictionary[i] = calloc(256, sizeof(UC));

    ULL n = fgetc(archive);
    n++;

    for (ULL i = 0; i < n; i++) {
        ULL x = getc(archive);
        ULL y = getc(archive);

        for (ULL j = 0; j < y / 8; j++) {
            ULL a = getc(archive);

            recover(a, dictionary[x], 8 * j, 8);
        }
        if (y % 8 != 0) {
            ULL a = getc(archive);

            recover(a, dictionary[x], y / 8 * 8, y % 8);
        }
    }

    UC *string = calloc(256, sizeof(UC));

    ULL buffer[2], t = 0;
    int c = getc(archive);

    buffer[1] = c;
    c = fgetc(archive);

    ULL a = 0;

    while (1) {
        buffer[0] = buffer[1];
        buffer[1] = c;

        if ((c = getc(archive)) == EOF)
            break;

        ULL x = (UC) buffer[0];
        x = backwards(x);

        for (ULL i = 0; i < 8; i++) {
            string[t++] = (x % 2) + '0';
            string[t] = '\0';

            x /= 2;

            for (int p = 0; p < 256; p++)
                if (strcmp((const char *) dictionary[p], (const char *) string) == 0) {
                    putc(p, decodedFile);
                    a++;
                    t = 0;

                    strcpy((char *) string, "");
                    break;
                }
        }
    }

    ULL x = buffer[0];
    x = backwards(x);

    for (ULL i = 0; i < 8 - (buffer[1] % 8); i++) {
        string[t++] = (x % 2) + '0';
        string[t] = '\0';
        x /= 2;

        for (int p = 0; p < 256; p++)
            if (strcmp((char *) dictionary[p], (char *) string) == 0) {
                putc(p, decodedFile);
                t = 0;
            }
    }

    fclose(archive);
    fclose(decodedFile);

    remove((const char *) archiveName);
    rename("._______________", (const char *) archiveName);
}

#endif //LAB15_ENCODINGDECODING_H