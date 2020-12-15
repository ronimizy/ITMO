//
// Created by Георгий Круглов on 14.11.2020.
//

#ifndef LAB14_LIFE_H
#define LAB14_LIFE_H

#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "config.h"

typedef struct lifeGameField field;

int isDead(pixel *p)
{
    return p->blue == CONFIG.inputScheme.dead.blue
            && p->green == CONFIG.inputScheme.dead.green
            && p->red == CONFIG.inputScheme.dead.red;
}

void mix(pixel *a, pixel *b, int* counter)
{
    if (CONFIG.fade)
    {
        a->blue = (a->blue + b->blue) / 2;
        a->green = (a->green + b->green) / 2;
        a->red = (a->red + b->red) / 2;
    }
    ++*counter;
}

struct lifeGameField
{
    int width;
    int height;

    pixel **current;

    int ages;
    pixel ***history;
};

field *LifeGame(int height, int width, pixel **array)
{
    field *game = (field *) malloc(sizeof(field));
    game->width = width;
    game->height = height;
    game->current = array;

    game->ages = 0;
    game->history = malloc(0);

    return game;
}

int livingRelatives(pixel **f, int i, int j, int height, int width, pixel *color)
{
    int a = 0;

    pixel *current = color;

    pixel *tl = &f[(i - 1 + height) % height][(j - 1 + width) % width];
    pixel *t = &f[(i - 1 + height) % height][j];
    pixel *tr = &f[(i - 1 + height) % height][(j + 1 + width) % width];

    pixel *l = &f[i][(j - 1 + width) % width];
    pixel *r = &f[i][(j + 1 + width) % width];

    pixel *bl = &f[(i + 1 + height) % height][(j - 1 + width) % width];
    pixel *b = &f[(i + 1 + height) % height][j];
    pixel *br = &f[(i + 1 + height) % height][(j + 1 + width) % width];

    if (!isDead(tl)) mix(current, tl, &a);
    if (!isDead(t)) mix(current, t, &a);
    if (!isDead(tr)) mix(current, tr, &a);

    if (!isDead(l)) mix(current, l, &a);
    if (!isDead(r)) mix(current, r, &a);

    if (!isDead(bl)) mix(current, bl, &a);
    if (!isDead(b)) mix(current, b, &a);
    if (!isDead(br)) mix(current, br, &a);

    return a;
}

int compareGenerations(field *f)
{
    for (int age = 0; age < f->ages; age++)
    {
        int a = 0;
        for (int i = 0; i < f->height; ++i)
        {
            for (int j = 0; j < f->width; ++j)
            {
                if (isDead(&(f->history[age][i][j])) == isDead(&(f->current[i][j]))) a++;
            }
        }
        if (a == (f->width) * (f->height)) return 1;
    }

    return 0;
}

void addToHistory(field *f)
{
    f->history = realloc(f->history, sizeof(pixel **) * (f->ages + 1));

    f->history[f->ages++] = f->current;

    f->current = malloc(sizeof(pixel *) * f->height);
    for (int i = 0; i < f->height; i++) f->current[i] = malloc(sizeof(pixel) * f->width);
}

int ageCycle(field *f)
{
    addToHistory(f);

    int living = 0;

    for (int i = 0; i < f->height; i++)
    {
        for (int j = 0; j < f->width; j++)
        {
            pixel **generation = f->history[f->ages - 1];

            pixel *genCell = &generation[i][j];
            pixel *curCell = &f->current[i][j];

            pixel color = *genCell;

            int relatives = livingRelatives(generation, i, j, f->height, f->width, &color);

            if (isDead(genCell) && relatives == 3)
            {
                *curCell = CONFIG.fade ? color : CONFIG.inputScheme.alive;
                living++;
            } else if (isDead(genCell)) *curCell = CONFIG.inputScheme.dead;

            if (!isDead(genCell) && (relatives < 2 || relatives > 3)) *curCell = CONFIG.inputScheme.dead;
            else if (!isDead(genCell))
            {
                living++;
                *curCell = color;
            }
        }
    }

    if (living == 0) return 1;
    if (compareGenerations(f) == 1) return 2;
    return 0;
}

void game(field *f)
{
    int result = ageCycle(f);
    int cycles = 1;

    char *fileName = makePath(CONFIG.outputDirectory, cycles, ".bmp\0");

    if (cycles % CONFIG.freq == 0) saveBMP(f->history[f->ages - 1], f->height, f->width, fileName);

    while (result == 0 && (CONFIG.maxIter == -1 || cycles < CONFIG.maxIter))
    {
        result = ageCycle(f);
        cycles++;
        if (cycles % CONFIG.freq == 0)
        {
            free(fileName);
            fileName = makePath(CONFIG.outputDirectory, cycles, ".bmp\0");

            saveBMP(f->history[f->ages - 1], f->height, f->width, fileName);
        }
    }

    printf("\n-----------------------------------------------------\n");
    printf("The game has ended with %d generations\n", cycles);
    printf(cycles == CONFIG.maxIter ? "Maximum cycles amount reached" : result == 1 ? "No living cells left" : "The game repeated itself");
    printf("\n-----------------------------------------------------\n");

    free(fileName);
}

#endif //LAB14_LIFE_H
