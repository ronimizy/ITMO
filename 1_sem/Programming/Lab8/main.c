#include <stdio.h>
#include <string.h>

int main() {

    char firstString[255], secondString[255], bufferString[255], bufferString2[255];
    int n, difference = 0;

//2. firstString + n elements of secondString
    printf("\n---- Прибавление n элементов первой строки ко второй ----\n");

    printf("Введите первую строку: ");
    scanf("%s", firstString);
    printf("Введите вторую строку: ");
    scanf("%s", secondString);
    printf("Введите n: ");
    scanf("%d", &n);
    strcpy(bufferString, firstString);
    strcpy(bufferString2, secondString);
    bufferString2[n] = '\0';
    strcat(bufferString, bufferString2);

    printf("\n%s\n", bufferString);

//4. compare first n symbols
    for (int i = 0; i < n; ++i) {
        if ((int) firstString[i] != (int) secondString[i]) {
            if ((int) firstString[i] < (int) secondString[i]) {
                difference = -1;
                break;
            } else {
                difference = 1;
                break;
            }
        }
    }
    printf("Первые %d символа(ов) %s\n", n, difference == 0
                                            ? "строк равны"
                                            : difference == -1
                                              ? "первой строки меньше второй"
                                              : "первой строки больше второй");

//9. Find last index of symbol
    printf("\n---- Нахождение последнего вхождения символа в строке ----\n");

    char symbolToFind;
    int index = -1;

    printf("Введите строку: ");
    scanf("%s", firstString);
    printf("Введите символ: ");
    scanf("%s", &symbolToFind);

    for (int i = (int) strlen(firstString) - 1; i >= 0; i--) {
        if ((int) firstString[i] == (int) symbolToFind) {
            index = i;
            break;
        }
    }
    symbolToFind == -1
    ? printf("\nСимвол не находится в строке\n")
    : printf("\nПоследнее вхождение символа имеет индекс: %d\n", index);

//11. Find length of the part of the firstString that contains symbols from the secondString
    printf("\n---- Нахождение длины наибольшего отрезка в первой строке, состоящего их элементов второй строки ----\n");

    int maxLength = 0, bufferLength = 0;

    printf("Введите первую строку: ");
    scanf("%s", firstString);
    printf("Введите вторую строку: ");
    scanf("%s", secondString);
    int firstStringLength = (int) strlen(firstString), secondStringLength = (int) strlen(secondString);

    for (int i = 0; i < firstStringLength; i++) {
        for (int j = 0; j < secondStringLength; j++) {
            if ((int) firstString[i] == (int) secondString[j]) {
                bufferLength++;
                j = (int) strlen(secondString);
            } else if (j == secondStringLength - 1) {
                if (bufferLength > maxLength) {
                    maxLength = bufferLength;
                }
                bufferLength = 0;
            }
        }
    }
    maxLength == 0
    ? printf("\nПервая строка не содержит символов второй\n")
    : printf("\nВ первой строке имеется отрезок в %d символов состоящий из символов второй строки\n", maxLength);

//13. Divide firstString by any symbol from secondString
    printf("\n---- Разделение первой строки символами из второй ----\n");

    strcpy(bufferString, "");
    printf("\nЛексемы: ");

    for (int i = 0; i < firstStringLength; i++) {
        for (int j = 0; j < secondStringLength; j++) {
            if ((int) firstString[i] == (int) secondString[j] || i == firstStringLength - 1) {
                printf("%s", bufferString);
                if (strlen(bufferString) != 0) {
                    if (i == firstStringLength - 1) {
                        printf("%c\n\n", firstString[firstStringLength - 1]);
                    } else {
                        printf(", ");
                    }
                }
                j = secondStringLength;
                strcpy(bufferString, "");
            } else if (j == secondStringLength - 1) {
                strcpy(bufferString2, &firstString[i]);
                bufferString2[1] = '\0';
                strcat(bufferString, bufferString2);
            }
        }
    }


    return 0;
}
