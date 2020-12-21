//
// Created by Георгий Круглов on 14.11.2020.
//

#ifndef LAB14_LIFE_H
#define LAB14_LIFE_H

#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "config.h"
#include "Expansion.h"

int isDead(PIXEL *p) {
    return p->blue == CONFIG.inputScheme.dead.blue
           && p->green == CONFIG.inputScheme.dead.green
           && p->red == CONFIG.inputScheme.dead.red;
}

void mix(PIXEL *a, PIXEL *b, int *counter) {
    ++*counter;
    if (a == 0)
        return;

    if (CONFIG.fade) {
        a->blue = (a->blue + b->blue) / 2;
        a->green = (a->green + b->green) / 2;
        a->red = (a->red + b->red) / 2;
    }
}

typedef struct {
    int height;
    int width;

    PIXEL **array;
} FRAME;

FRAME *newFrame(int height, int width) {
    FRAME *frame = malloc(sizeof(FRAME));

    frame->height = height;
    frame->width = width;

    frame->array = calloc(height, sizeof(PIXEL *));

    for (int i = 0; i < height; i++)
        frame->array[i] = calloc(width, sizeof(PIXEL));

    return frame;
}

typedef struct {
    FRAME *current;

    int ages;
    FRAME **history;
} FIELD;

FIELD *LifeGame(int height, int width, PIXEL **array) {
    FIELD *game = malloc(sizeof(FIELD));
    game->current = malloc(sizeof(FRAME));

    game->current->height = height;
    game->current->width = width;
    game->current->array = array;

    game->ages = 0;
    game->history = malloc(0);

    return game;
}

int withinRange(int i, int j, int height, int width) {
    return i >= 0 && i < height && j >= 0 && j < width;
}

int livingRelatives(PIXEL **f, int i, int j, int height, int width, PIXEL *color) {
    int a = 0;

    PIXEL *current = color;

    PIXEL *tl = withinRange(i - 1, j - 1, height, width)
                ? &f[i - 1][j - 1] : 0;
    PIXEL *t = withinRange(i - 1, j, height, width)
               ? &f[(i - 1 + height) % height][j] : 0;
    PIXEL *tr = withinRange(i - 1, j + 1, height, width)
                ? &f[(i - 1 + height) % height][(j + 1 + width) % width] : 0;

    PIXEL *l = withinRange(i, j - 1, height, width)
               ? &f[i][(j - 1 + width) % width] : 0;
    PIXEL *r = withinRange(i, j + 1, height, width)
               ? &f[i][(j + 1 + width) % width] : 0;

    PIXEL *bl = withinRange(i + 1, j - 1, height, width)
                ? &f[(i + 1 + height) % height][(j - 1 + width) % width] : 0;
    PIXEL *b = withinRange(i + 1, j, height, width)
               ? &f[(i + 1 + height) % height][j] : 0;
    PIXEL *br = withinRange(i + 1, j + 1, height, width)
                ? &f[(i + 1 + height) % height][(j + 1 + width) % width] : 0;

    if (tl != 0 && !isDead(tl)) mix(current, tl, &a);
    if (t != 0 && !isDead(t)) mix(current, t, &a);
    if (tr != 0 && !isDead(tr)) mix(current, tr, &a);

    if (l != 0 && !isDead(l)) mix(current, l, &a);
    if (r != 0 && !isDead(r)) mix(current, r, &a);

    if (bl != 0 && !isDead(bl)) mix(current, bl, &a);
    if (b != 0 && !isDead(b)) mix(current, b, &a);
    if (br != 0 && !isDead(br)) mix(current, br, &a);

    return a;
}

int compareGenerations(FIELD *f) {
    for (int age = 0; age < f->ages; age++) {
        int a = 0;
        if (f->history[age]->height != f->current->height || f->history[age]->width != f->current->width)
            continue;
        for (int i = 0; i < f->current->height; ++i) {
            for (int j = 0; j < f->current->width; ++j) {
                if (isDead(&(f->history[age]->array[i][j])) == isDead(&(f->current->array[i][j]))) a++;
            }
        }
        if (a == (f->current->width) * (f->current->height)) return 1;
    }

    return 0;
}

void addToHistory(FIELD *f) {
    f->history = realloc(f->history, sizeof(FRAME *) * (f->ages + 1));

    f->history[f->ages++] = f->current;

    f->current = newFrame(f->current->height, f->current->width);
}

int ageCycle(FIELD *f) {
    addToHistory(f);

    int living = 0;

    int offsetI = 0;
    int offsetJ = 0;

    PIXEL **generation = f->history[f->ages - 1]->array;

    for (int i = -1; i <= f->history[f->ages - 1]->height; i++) {

        for (int j = -1; j <= f->history[f->ages - 1]->width; j++) {

            PIXEL *genCell = &generation[i][j];
            PIXEL *curCell = &f->current->array[i + offsetI][j + offsetJ];

            PIXEL color = (i > -1 && i < f->history[f->ages - 1]->height
                    && j > -1 && j < f->history[f->ages - 1]->width)
                          ? *genCell : CONFIG.inputScheme.alive;

            int relatives = livingRelatives(generation, i, j,
                                            f->history[f->ages - 1]->height,
                                            f->history[f->ages - 1]->width,
                                            &color);

            if (!withinRange(i, j, f->history[f->ages - 1]->height, f->history[f->ages - 1]->width)) {
                if (relatives == 3) {
                    if (i == -1 || i == f->history[f->ages - 1]->height) {
                        f->current->array = (PIXEL **) expand((void **) f->current-> array,
                                                              &f->current->height,
                                                              &f->current->width,
                                                              sizeof(PIXEL ),
                                                              i == -1 ? top : bottom,
                                                              &CONFIG.inputScheme.dead);

                        offsetI += i == -1 ? 1 : 0;
                    }
                    if (j == -1 || j == f->history[f->ages - 1]->width) {
                        f->current->array = (PIXEL **) expand((void **) f->current->array,
                                                              &f->current->height,
                                                              &f->current->width,
                                                              sizeof(PIXEL ),
                                                              j == -1 ? leading : trailing,
                                                              &CONFIG.inputScheme.dead);

                        offsetJ += j == -1 ? 1 : 0;
                    }

                    f->current->array[i + offsetI][j + offsetJ] = CONFIG.fade ? color : CONFIG.inputScheme.alive;
                }

                continue;
            }



            if (isDead(genCell) && relatives == 3) {
                *curCell = CONFIG.fade ? color : CONFIG.inputScheme.alive;
                living++;
            } else if (isDead(genCell))
                *curCell = CONFIG.inputScheme.dead;

            if (!isDead(genCell) && (relatives < 2 || relatives > 3))
                *curCell = CONFIG.inputScheme.dead;
            else if (!isDead(genCell)) {
                living++;
                *curCell = color;
            }
        }
    }

    if (living == 0) return 1;
    if (compareGenerations(f) == 1) return 2;
    return 0;
}

void game(FIELD *f) {
    int result = ageCycle(f);
    int cycles = 1;

    char *fileName = makePath(CONFIG.outputDirectory, cycles, ".bmp\0");

    if (cycles % CONFIG.freq == 0)
        saveBMP(f->history[f->ages - 1]->array,
                f->history[f->ages - 1]->height,
                f->history[f->ages - 1]->width,
                fileName);

    while (result == 0 && (CONFIG.maxIter == -1 || cycles < CONFIG.maxIter)) {
        result = ageCycle(f);
        cycles++;
        if (cycles % CONFIG.freq == 0) {
            free(fileName);
            fileName = makePath(CONFIG.outputDirectory, cycles, ".bmp\0");

            saveBMP(f->history[f->ages - 1]->array,
                    f->history[f->ages - 1]->height,
                    f->history[f->ages - 1]->width,
                    fileName);
        }
    }

    printf("\n-----------------------------------------------------\n");
    printf("The game has ended with %d generations\n", cycles);
    printf(cycles == CONFIG.maxIter ? "Maximum cycles amount reached" : result == 1 ? "No living cells left"
                                                                                    : "The game repeated itself");
    printf("\n-----------------------------------------------------\n");

    free(fileName);
}

#endif //LAB14_LIFE_H
