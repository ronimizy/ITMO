#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char string[256];
    printf("Введите строку:");
    scanf("%s", string);

    int numbersCount = 0, smolCount = 0, bigCount = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if ((int)string[i] > 47 && (int)string[i] < 58) { numbersCount++; }
        if ((int)string[i] > 63 && (int)string[i] < 91) { bigCount++; }
        if ((int)string[i] > 96 && (int)string[i] < 123) { smolCount++; }
    }

    printf("Количество цифр в строке: %d "
           "\nКоличество строчных букв в строке: %d "
           "\nКоличество прописных букв в строке: %d",
           numbersCount, smolCount, bigCount);



    int number;
    printf("\nВведите число:");
    scanf("%d", &number);
    int *grid = malloc((number+1)*sizeof(int));
    for (int i = 0; i <= number; i++) { grid[i] = 1; }
    for (int i = 2; i <= number; i++)
    {
        if (grid[i] == 1)
        {
            printf("%d ", i);
            for (int j = 2*i; j <= number; j+= i) { grid[j] = 0; }
        }
    }


    return 0;
}
