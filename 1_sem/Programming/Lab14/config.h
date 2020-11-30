//
// Created by Георгий Круглов on 18.11.2020.
//

#ifndef LAB14_CONFIG_H
#define LAB14_CONFIG_H

#include "color.h"



typedef struct lifeGameConfig config;

struct lifeGameConfig
{
    char *inputFile;
    char *outputDirectory;

    int maxIter;
    int freq;

    scheme inputScheme;
    scheme outputScheme;
    int oSchemeSet;

    int fade;
    int gif;

    int inputScale;
    int outputScale;
};

config CONFIG;

void Default()
{
    CONFIG.inputFile = 0;
    CONFIG.outputDirectory = 0;
    CONFIG.maxIter = -1;
    CONFIG.freq = 1;
    CONFIG.inputScheme = Dark();
    CONFIG.outputScheme = Dark();
    CONFIG.oSchemeSet = 0;
    CONFIG.fade = 0;
    CONFIG.gif = 0;
    CONFIG.inputScale = 1;
    CONFIG.outputScale = 1;
}


#endif //LAB14_CONFIG_H
