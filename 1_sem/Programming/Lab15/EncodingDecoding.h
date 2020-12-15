//
// Created by Георгий Круглов on 04.12.2020.
//

#ifndef LAB15_ENCODINGDECODING_H
#define LAB15_ENCODINGDECODING_H

typedef unsigned long long ULL;
typedef unsigned char UC;

typedef struct node {
    ULL frequency;
    UC character;
    struct node *left, *right;
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

void mergeSort(ULL size, NODE **array) {
    if (size == 1) { return; }
    ULL divideIndex = size / 2;
    NODE *leftArray[divideIndex], *rightArray[size - divideIndex];

    for (int i = 0; i < divideIndex; i++) {
        leftArray[i] = array[i];
    }
    for (int i = divideIndex; i < size; i++) {
        rightArray[i - divideIndex] = array[i];
    }

    mergeSort(divideIndex, leftArray);
    mergeSort(size - divideIndex, rightArray);

    merge(divideIndex, leftArray, size - divideIndex, rightArray, array);
}

NODE *connectNodes(NODE *left, NODE *right) {
    NODE *n = malloc(sizeof(NODE));

    n->left = left;
    n->right = right;

    n->frequency = left->frequency + right->frequency;
    n->character = -1;

    return n;
}

void code(NODE *n, UC *string, ULL size, UC **dictionary) {
    if (n->right == NULL) {
        strcpy((char *) dictionary[n->character], (char *) string);
        return;
    }

    string[size + 1] = '\0';
    string[size] = '1';
    code(n->right, string, size + 1, dictionary);

    string[size + 1] = '\0';
    string[size] = '0';
    code(n->left, string, size + 1, dictionary);
}

void recover(ULL value, UC *string, ULL start, ULL end) {
    for (ULL i = 0; i < end; i++) {
        string[start + end - 1 - i] = value % 2 + '0';
        value /= 2;
    }
    string[start + end] = '\0';
}

ULL backwards(ULL value) {
    ULL buf = 0;

    for (ULL i = 0; i < 8; i++) {
        buf = buf * 2 + value % 2;
        value /= 2;
    }

    return buf;
}


UC *encode(const UC *inputData, ULL *dataSize) {
    UC **dictionary = calloc(256, sizeof(UC *));
    ULL *frequency = calloc(256, sizeof(ULL));

    //Создаём словарь, зануляем встречаемость
    for (ULL i = 0; i < 256; i++) {
        dictionary[i] = calloc(256, sizeof(UC));
        strcpy((char *) dictionary[i], "");
        frequency[i] = 0;
    }


    NODE **tree = calloc(256, sizeof(NODE *));

    //Заполняем встречаемость
    for (ULL i = 0; i < *dataSize; i++)
        frequency[inputData[i]]++;

    //Формируем дерево
    ULL k = 0;
    for (ULL i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            NODE *n = malloc(sizeof(NODE));

            n->character = i;
            n->frequency = frequency[i];
            n->left = NULL;
            n->right = NULL;
            tree[k++] = n;
        }
    }

    ULL letterCount = k;

    mergeSort(k, tree);

    //Соединяем узлы дерева
    while (k != 1) {
        tree[k - 2] = connectNodes(tree[k - 2], tree[k - 1]);
        k--;
    }

    UC *string = calloc(256, sizeof(UC));
    ULL size = 0;

    //Заполняем коды
    code(tree[0], string, size, dictionary);

    UC *data = calloc(*dataSize + letterCount + 1, sizeof(UC));
    data[*dataSize + letterCount] = '\0';
    ULL ptr = 0;

    //Запись размера алфавита
    data[ptr++] = letterCount;

    //Запись алфавита
    for (ULL i = 0; i < 256; i++) {
        if (frequency[i] != 0) {
            ULL binaryInterp = 0, count = 0, length = strlen((char *) dictionary[i]);

            data[ptr++] = i;
            data[ptr++] = length;

            for (ULL j = 0; j < length; j++) {
                binaryInterp = binaryInterp * 2 + (dictionary[i][j] == '0' ? 0 : 1);
                count++;

                if (count == 8) {
                    data[ptr++] = binaryInterp;

                    binaryInterp = 0;
                    count = 0;
                }
            }
            if (count != 0) {
                data[ptr++] = binaryInterp;
            }
        }
    }

    //Запись данных в закодированном виде
    ULL binaryInterp = 0, count = 0;

    for (ULL i = 0; i < *dataSize; i++) {
        for (ULL j = 0; dictionary[inputData[i]][j] != '\0'; j++) {
            binaryInterp = binaryInterp * 2 + (dictionary[inputData[i]][j] - '0');
            count++;

            if (count == 8) {
                data[ptr++] = binaryInterp;

                binaryInterp = 0;
                count = 0;
            }
        }
    }
    if (count != 0) {
        data[ptr++] = binaryInterp << (8 - count);
    }
    data[ptr++] = 8 - count;
    data[ptr++] = '\0';

    for (int i = 0; i < 256; i++) {
        free(dictionary[i]);
        free(tree[i]);
    }
    free(dictionary);
    free(tree);
    free(frequency);
    free(string);

    *dataSize = ptr;

    data = realloc(data, ptr);

    return data;
}

UC *decode(UC *inputData, ULL *dataSize) {
    UC **dictionary = calloc(256, sizeof(UC *));
    for (ULL i = 0; i < 256; i++)
        dictionary[i] = calloc(256, sizeof(UC));

    //Восстановление и заполнение алфавита
    ULL alphabetSize = (ULL) inputData[0];
    ULL ptr = 1;

    for (ULL i = 0; i < alphabetSize; i++) {
        ULL value = inputData[ptr++], size = inputData[ptr++];

        for (ULL j = 0; j < size / 8; j++) {
            ULL buf = inputData[ptr++];

            recover(buf, dictionary[value], 8 * j, 8);
        }
        if (size % 8 != 0) {
            ULL buf = inputData[ptr++];

            recover(buf, dictionary[value], (size / 8) * 8, size % 8);
        }
    }

    UC *string = calloc(256, sizeof(UC));
    UC *data = calloc(*dataSize - ptr + 1, sizeof(UC));
    data[*dataSize - ptr] = '\0';

    ULL count = 0;
    ULL i = ptr;
    ptr = 0;
    for (; i < *dataSize; i++) {
        ULL x = backwards(inputData[i]);

        for (ULL j = 0; j < 8; j++) {
            string[count++] = (x % 2) + '0';
            string[count] = '\0';

            x /= 2;

            for (ULL iter = 0; iter < 256; iter++) {
                if (strcmp((char *) string, (char *) dictionary[iter]) == 0) {
                    data[ptr++] = iter;

                    count = 0;
                    strcpy((char *) string, "");

                    break;
                }
            }
        }
    }

    ULL x = backwards(inputData[*dataSize - 2]);

    for (i = 0; i < 8 - (inputData[*dataSize - 1] % 8); i++) {
        string[count++] = (x % 2) + '0';
        string[count] = '\0';

        x /= 2;

        for (ULL iter = 0; iter < 256; iter++) {
            if (strcmp((char *) string, (char *) dictionary[iter]) == 0) {
                data[ptr++] = iter;

                count = 0;
                strcpy((char *) string, "");

                break;
            }
        }
    }

    for (i = 0; i < 256; i++)
        free(dictionary[i]);
    free(dictionary);
    free(string);


    *dataSize = ptr;

    return data;
}


#endif //LAB15_ENCODINGDECODING_H