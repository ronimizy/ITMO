//
// Created by Георгий Круглов on 24.11.2020.
//

#ifndef LAB14_GIF_H
#define LAB14_GIF_H

#include "color.h"
#include "life.h"
#include "config.h"
#include "bmp.h"
#include <math.h>
#include <time.h>

int* rlcOne(int* before, long oldSize, long newSize)
{
    int* n = calloc(newSize, sizeof(int));
    for (int i = 0; i < oldSize; i++) n[i] = before[i];

    free(before);
    return n;
}

pixel* rlcOnePxl(pixel * before, int oldSize, int newSize)
{
    pixel * n = calloc(newSize, sizeof(int));
    for (int i = 0; i < oldSize; i++) n[i] = before[i];

    free(before);
    return n;
}

int** rlcTwo(int** b, int oO, int* oT, int nO, int* nT)
{
    int **r = calloc(nO, sizeof(int *));
    for (int i = 0; i < nO; i++) r[i] = calloc(nT[i], sizeof(int));

    for (int i = 0; i < oO; i++)
        for (int j = 0; j < oT[i]; j++)
            r[i][j] = b[i][j];

    for (int i = 0; i < oO; i++) free(b[i]);
    free(b);

    return r;
}

void makeGIF(field *f)
{
    char* path = makePath(CONFIG.outputDirectory, f->ages, ".gif\0");
    FILE *gif = fopen(path, "wb");

    int colorCount = 0;

    //Создание масштабированного набора изображний
    pixel ***scaled = calloc(f->ages, sizeof(pixel**));
        //Масштабирование изображения каждого поколения
    for (int i = 0; i < f->ages; i++) scaled[i] = scale(f->history[i], CONFIG.outputScale, f->height, f->width);

    //Создание таблицы цветов
    pixel *colorTable = calloc(0, 0);

    //Создание набора изображений с кодами цветов вместо самих цветов
    int ***coded = calloc(f->ages, sizeof(int**));
    for (int a = 0; a < f->ages; a++)
    {
        coded[a] = calloc(f->height*CONFIG.outputScale, sizeof(int*));
        for (int i = 0; i < f->height*CONFIG.outputScale; i++)
            coded[a][i] = calloc(f->width*CONFIG.outputScale, sizeof(int));
    }


        //Заполнение "coded" кодами цветов
    for (int age = 0; age < f->ages; age++)
        for (int h = 0; h < f->height*CONFIG.outputScale; h++)
            for (int w = 0; w < f->width*CONFIG.outputScale; w++)
            {
                for (int c = 0; c < colorCount; c++)
                {
                        //Если пиксель из таблицы цветов равен проверяемому пикселю
                    if (equal(&colorTable[c], &scaled[age][h][w]))
                    {
                        //Записываем в соответствующий "пиксель" из "coded" его код
                        coded[age][h][w] = c;
                        break;
                    }
                        //Если мы в конце таблицы и не нашли нужный цвет
                    else if (c == colorCount - 1)
                    {
                            //Расширям таблицу цветов
                        colorTable = rlcOnePxl(colorTable, colorCount, colorCount+1);
                            //Добавляем в неё цвет
                        colorTable[colorCount++] = scaled[age][h][w];
                            //Записываем в соответствующий "пиксель" из "coded" его код
                        coded[age][h][w] = colorCount-1;
                        break;
                    }
                }
                    //Если таблица цветов пустая
                if (colorCount == 0)
                {
                        //Расширяем таблицу цветов
                    colorTable = rlcOnePxl(colorTable, colorCount, colorCount +1 );
                        //Добавляем в неё цвет
                    colorTable[colorCount++] = scaled[age][h][w];
                        //Записываем в соответствующий "пиксель" из "coded" его код
                    coded[age][h][w] = colorCount-1;
                }
            }

    for (int i = 0; i < f->ages; i++)
    {
        for (int j = 0; j < f->height*CONFIG.outputScale; j++)
            free(scaled[i][j]);
        free(scaled[i]);
    }
    free(scaled);

    int sizeMark = 0;
    while (pow((double )2, (double )sizeMark+1) < colorCount) sizeMark++;
    int bPP = sizeMark+1;
    bPP = bPP == 1 ? 2 : bPP;

    //Заголовок
    fwrite("GIF89a", sizeof(char), strlen("GIF87a"), gif);

    dtox(gif, CONFIG.outputScale*f->width, 2);
    dtox(gif, CONFIG.outputScale*f->height, 2);

    dtox(gif, (1<<7) + (1<<6) + sizeMark, 1);

    dtox(gif, 0, 1);
    dtox(gif, 0, 1);

    for (int i = 0; i < colorCount; i++) putcolor(gif, &colorTable[i]);

    //Netscape
    dtox(gif, '!', 1); //Код тега
    dtox(gif, 255, 1);
    dtox(gif, 11, 1);

    dtox(gif, 'N', 1); //Имя тега
    dtox(gif, 'E', 1);
    dtox(gif, 'T', 1);
    dtox(gif, 'S', 1);
    dtox(gif, 'C', 1);
    dtox(gif, 'A', 1);
    dtox(gif, 'P', 1);
    dtox(gif, 'E', 1);
    dtox(gif, '2', 1);
    dtox(gif, '.', 1);
    dtox(gif, '0', 1);

    dtox(gif, 3, 1); //3
    dtox(gif, 1, 1); //Пустой бит
    dtox(gif, 0, 2); //Количетво повторов
    dtox(gif, 0 ,1); //Конец

    //Данные кадров
    for (int age = 0; age < f->ages; ++age)
    {
        //Управление графикой
        dtox(gif, '!', 1); //Код тега
        dtox(gif, 249, 1);
        dtox(gif, 4, 1);
        dtox(gif, 4, 1); //Disp

        dtox(gif, 0, 2); //Задержка

        dtox(gif, 0, 1); //Код прозрачного цвета
        dtox(gif, 0, 1); //Конец

        //Заголовок картинки
        dtox(gif, ',', 1);

        dtox(gif, 0, 2);
        dtox(gif, 0, 2);

        dtox(gif, CONFIG.outputScale*f->width, 2);
        dtox(gif, CONFIG.outputScale*f->height, 2);

        dtox(gif, 0, 1);

        //Длина таблицы кодирования
        int lzwLen = (int) pow(2, bPP) + 2;
        //Таблица кодирования
        int **lzw = calloc(lzwLen, sizeof(int*));
        //Массив количества символов в каждой ячейки таблицы кодирования
        int *lzwSize = calloc(lzwLen, sizeof(int ));
            //Заполнение таблицы кодирования начальными значениями
        for (int i = 0; i < colorCount+2; i++)
        {
            lzw[i] = calloc(1, sizeof(int));
            lzw[i][0] = i;
            lzwSize[i] = 1;
        }

        //Массив кодированый LZW
        int *ans = calloc(1, sizeof(int )), ansSize = 1;
            //<CC>
        ans[0] = lzwLen-2;
        //Текущая цепочка
        int *buf = calloc(0, 0), bufSize = 0;
        //Код из таблицы кодирования для префикса текущей цепочки
        int ptr = -1;

        //Кодирование
        for (int h = 0; h < f->height*CONFIG.outputScale; h++)
            for (int w = 0; w < f->width*CONFIG.outputScale; w++)
            {
                //Расширяем цепочку
                buf = rlcOne(buf, bufSize, bufSize+1);
                    //Добавляем символ к цепочке
                buf[bufSize++] = coded[age][h][w];

                    //Код в таблице кодирования для текущей цепочки
                int index = -1;

                for (int row = 0; row < lzwLen; row++)
                {
                        //Размер текущей цепочки не равен размеру проверяемой цепочки в таблице кодирования
                    if (bufSize != lzwSize[row]) continue;
                    else
                    {
                            //Посимвольная проверка равенства между текущей цепочкой и проверяемой цепочкой таблицы кодирования
                        for (int c = 0; c < lzwSize[row]; c++)
                        {
                                //Если символ не равен - цепочка не равна текущей
                            if (buf[c] != lzw[row][c]) break;
                                //Если символ равен и он последний - цепочка равна текущей
                            if (c == lzwSize[row] - 1) index = row;
                        }
                    }
                }

                //Если в таблице нет цепочки равной текущей
                if (index == -1)
                {
                    //Расширяем массив ответов
                    ans = rlcOne(ans, ansSize, ansSize + 1);
                        //Записываем код префикса текущей цепочки
                    ans[ansSize++] = ptr;

                        //Расширяем массив размеров таблицы кодирования
                    lzwSize = rlcOne(lzwSize, lzwLen, lzwLen+1);
                        //Записываем для новой цепочки размер текущей цепочки
                    lzwSize[lzwLen] = bufSize;

                        //Расширяем таблицу кодирования
                    lzw = rlcTwo(lzw, lzwLen, lzwSize, lzwLen+1, lzwSize);
                        //Записываем в неё текущую цепочку
                    lzw[lzwLen++] = buf;

                    //Берём последний символ и присваеваем его текущей цепочке
                    int b = buf[bufSize-1];
                    buf = calloc(1, sizeof(int ));
                    buf[0] = b;
                    bufSize = 1;

                    //Присваеваем "ptr" код последнего символа
                    for (int i = 0; i < lzwLen; i++) if (lzwSize[i] == 1 && lzw[i][0] == b) ptr = i;
                }
                else
                {
                    ptr = index;
                }
            }

        //Расширяем массив ответов
        ans = rlcOne(ans, ansSize, ansSize+1);
            //Записываем в него "EOI"
        ans[ansSize++] = (int) pow(2, bPP) + 1;


        dtox(gif, colorCount == 1 ? 2 : colorCount, 1); //Минимальный размер кода

        for (int i = 0; i < ansSize; i++) printf("%d ", ans[i]); //Вывод массива ответов на консоль (дебаг)
        printf("\n");
        printf("\n");


        //Размер выводимого кода
        long size = bPP;
        //Количество бит записанных в буфер массив
        long length = 0;

        //Буффер массив
        int *arr = calloc(0, 0);


        for (int i = 0; i < ansSize; i++)
        {
            //Доведение размера выводимого кода до релевантности
            while (pow(2, (double )size) <= ans[i]) size++;

            //Очередной перекодируемый элемент
            int buffer = ans[i];

            //Занесение кода побитно в буфер массив
            for (int j = 0; j < size; j++)
            {
                arr = rlcOne(arr, length, length+1);
                arr[length++] = buffer%2;
                buffer /= 2;
            }
        }

        //Количество дополнительных нулевых битов для кратности 8
        int blank = (int) (length%8);
        blank = blank == 0 ? 0 : 8 - blank;

        dtox(gif, (int) ((length+blank)/8), 1); //Размер закодированного изображения в байтах

        //Итератор
        long iter = 0;

        //Пока итератор не пройдет по каждому биту
        while (iter < length)
        {
            //Количество битов которые будут записаны из массива
            int offset = 8;

            //Если осталось меньше 8 битов
            if (length - iter < 8 && blank > 0)
            {
                //Вычисляем сколько битов нужно оставить пустыми
                blank -= offset;
                offset = blank > 0 ? 0 : -blank;
            }

            //Биты для записи
            int add = 0;

            //Добавсление битов в буфер переменную
            for (int i = 0; i < offset; i++)
                add += arr[iter++] * (int) pow(2, i);

            fputc(add, gif);
        }

        //Конец изображения
        dtox(gif, 0 ,1);

        for (int i = 0; i < lzwLen; i++)
            free(lzw[i]);
        free(lzw);
        free(lzwSize);
        free(ans);
        free(buf);
        free(arr);
    }

    dtox(gif, 59, 1);

    fclose(gif);

    free(path);
    free(colorTable);

    for (int age = 0; age < f->ages; age++)
    {
        for (int h = 0; h < f->height; h++)
            free(coded[age][h]);
        free(coded[age]);
    }
    free(coded);
}

#endif //LAB14_GIF_H
