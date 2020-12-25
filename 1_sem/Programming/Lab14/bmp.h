//
// Created by Георгий Круглов on 14.11.2020.
//


#ifndef LAB14_BMP_H
#define LAB14_BMP_H

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "color.h"
#include "config.h"

int numCount(int a)
{
    int c = 0;
    while (a > 0)
    {
        a /= 10;
        c++;
    }
    return c;
}

int equal(PIXEL *a, PIXEL *b)
{
    return a->red == b->red
           && a->green == b->green
           && a->blue == b->blue;
}

char* makePath(char* directory, int order, char* extention)
{
    int size = numCount(order);
    int dirLen = (int) strlen(directory);

    char *name = malloc(size + 1);
    sprintf(name, "%d", order);
    name[size] = '\0';

    char *path = malloc(dirLen + strlen(name) + strlen(extention));
    strcpy(path, directory);
    strcat(path, name);
    strcat(path, extention);

    free(name);
    return path;
}

void intTo16(FILE* f, int a, int size)
{
    //printf("%d\n", a);
    for (int i = 0; i < size; i++)
    {
        fputc(a % 256, f);
        a /= 256;
    }
//    fputc(a % 256, f);
//    fputc(a / 256 % 256, f);
//    fputc(a / 256 / 256 % 256, f);
//    fputc(a / 256 / 256 / 256 % 256, f);
}

void arrayInverse(PIXEL **array, int height)
{
    PIXEL **n = malloc(sizeof(PIXEL*) * height);

    for (int i = 0; i < height; i++)
    {
        n[i] = array[height-i-1];
    }
    for (int i = 0; i < height; i++)
    {
        array[i] = n[i];
    }

    free(n);
}

void putcolor(FILE *f, PIXEL *a)
{
    fputc(a->blue % 256, f);
    fputc(a->green % 256, f);
    fputc(a->red % 256, f);
}

void getColor(FILE *f, PIXEL* a)
{
    a->blue = (int) fgetc(f) % 256;
    if (a->blue < 0)
        a->blue = 256 + a->blue;

    a->green = (int) fgetc(f) % 256;
    if (a->green < 0)
        a->green = 256 + a->green;

    a->red = (int) fgetc(f) % 256;
    if (a->red < 0)
        a->red = 256 + a->red;
}

void intFrom16(FILE* f, int* a)
{
    *a = 0;
    *a += fgetc(f);
    *a += fgetc(f) * 256;
    *a += fgetc(f) * 256 * 256;
    *a += fgetc(f) * 256 * 256 * 256;
}

void saveBMP(PIXEL **array, int height, int width, char* fileName)
{
    FILE *f = fopen(fileName, "wb");

    //Type
    fputc('B', f);
    fputc('M', f);

    int offset = 0;
    while ((width*3*CONFIG.outputScale + offset)%4 !=0) offset++;

    //File Size
    dtox(f, 56 + (int) (sizeof(int ) * height * (width + offset)* CONFIG.outputScale * CONFIG.outputScale), 4);

    //res1 & res2
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);

    //Offset Bits
    dtox(f, 54, 4);

    //Header Size
    dtox(f,40, 4);

    //Width
    dtox(f, width*CONFIG.outputScale, 4);

    //Height
    dtox(f, height*CONFIG.outputScale, 4);

    //Planes
    fputc(1, f);
    fputc(0, f);

    //Bit Depth
    fputc(24, f);
    fputc(0, f);

    //Compression
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);

    //Image Size
    dtox(f, (width)*height*CONFIG.outputScale * CONFIG.outputScale, 4);

    //PPM
    fputc(195, f);
    fputc(14, f);
    fputc(0, f);
    fputc(0, f);

    fputc(195, f);
    fputc(14, f);
    fputc(0, f);
    fputc(0, f);

    //Colors used
    fputc(2, f);
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);

    //Colors important
    fputc(2, f);
    fputc(0, f);
    fputc(0, f);
    fputc(0, f);

    arrayInverse(array, height);

    for (int i = 0; i < height; i++)
    {
        for (int scaleV = 0; scaleV < CONFIG.outputScale; scaleV++)
        {
            for (int j = 0; j < width; j++)
            {
                for (int scaleH = 0; scaleH < CONFIG.outputScale; scaleH++)
                {
                    if (equal(&array[i][j], &CONFIG.inputScheme.dead))
                    {
                        putcolor(f, &CONFIG.outputScheme.dead);
                    }
                    else if (equal(&array[i][j], &CONFIG.inputScheme.alive))
                    {
                        putcolor(f, &CONFIG.outputScheme.alive);
                    }
                    else
                    {
                        putcolor(f, &array[i][j]);
                    }
                }
            }
            for (int k = 0; k < offset; k++) fputc(0, f);
        }
    }

    fclose(f);
}

PIXEL** openBMP(int* height, int* width)
{
    FILE *f = fopen(CONFIG.inputFile, "rb");

    if (f == 0)
    {
        printf("File is NULL");
        exit(0);
    }

    fseek(f, 18, SEEK_SET);
    xtod(f, width);
    *width /= CONFIG.inputScale;
    xtod(f, height);
    *height /= CONFIG.inputScale;

    PIXEL **array = malloc(sizeof(PIXEL *) * (*height));
    for (int i = 0; i < *height; i++) array[i] = malloc(sizeof(PIXEL) * (*width));

    int offset = 0;
    while ((*width*3*CONFIG.inputScale + offset)%4 !=0) offset++;

    fseek(f, 54, SEEK_SET);
    for (int i = 0; i < *height; i++)
    {
        for (int j = 0; j < *width; j++)
        {
            getColor(f, &array[i][j]);
            fseek(f, 3*CONFIG.inputScale - 3, SEEK_CUR);
        }
        for (int k = 0; k < offset; k++) fgetc(f);
        fseek(f, (3*(*width)*CONFIG.inputScale + offset)*(CONFIG.inputScale - 1), SEEK_CUR);
    }

    arrayInverse(array, (*height));


    return array;
};

#endif //LAB14_BMP_H