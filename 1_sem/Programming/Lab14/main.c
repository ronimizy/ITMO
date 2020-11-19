#include <stdio.h>
#include "life.h"

#define debug

int main(int argc, char **argv)
{

#ifdef debug
    argc = 14;
    argv[1] = "--input";
    argv[2] = "pulsar_20.bmp";
    argv[3] = "--output";
    argv[4] = "prs/";
    argv[5] = "--max_iter";
    argv[6] = "5";
    argv[7] = "--dump_freq";
    argv[8] = "1";
    argv[9] = "--output_scheme";
    argv[10] = "dark";
    argv[11] = "--output_scale";
    argv[12] = "11";
    argv[13] = "--input_scale";
    argv[14] = "20";
#endif

    Default();

    for (int i = 1; i < argc; i++)
    {
        if (strcmp("--input", argv[i]) == 0)
        {
            CONFIG.inputFile = malloc(strlen(argv[i+1]) +1);
            strcpy(CONFIG.inputFile, argv[i+1]);
            CONFIG.inputFile[strlen(argv[i+1])] = '\0';
        }
        else if (strcmp("--output", argv[i]) == 0)
        {
            CONFIG.outputDirectory = malloc(strlen(argv[i+1]) + 1);
            strcpy(CONFIG.outputDirectory, argv[i+1]);
            CONFIG.outputDirectory[strlen(argv[i+1])] = '\0';

            mkdir(CONFIG.outputDirectory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        else if (strcmp("--max_iter", argv[i]) == 0)
        {
            CONFIG.maxIter = atoi(argv[i+1]);
        }
        else if (strcmp("--dump_freq", argv[i]) == 0)
        {
            CONFIG.freq = atoi(argv[i+1]);
        }
        else if (strcmp("--input_scheme", argv[i]) == 0)
        {
            if (strcmp("light", argv[i+1]) == 0)
            {
                CONFIG.inputScheme = Light();
            }
            else
            {
                CONFIG.inputScheme = Dark();
            }
            if (CONFIG.oSchemeSet == 0) CONFIG.outputScheme = CONFIG.inputScheme;
        }
        else if (strcmp("--output_scheme", argv[i]) == 0)
        {
            if (strcmp("light", argv[i+1]) == 0)
            {
                CONFIG.outputScheme = Light();
            }
            else
            {
                CONFIG.outputScheme = Dark();
            }
            CONFIG.oSchemeSet = 1;
        }
        else if (strcmp("--fade", argv[i]) == 0)
        {
            CONFIG.fade = 1;
        }
        else if (strcmp("--input_scale", argv[i]) == 0)
        {
            CONFIG.inputScale = atoi(argv[i+1]);
        }
        else if (strcmp("--output_scale", argv[i]) == 0)
        {
            CONFIG.outputScale = atoi(argv[i+1]);
        }
    }

    if (CONFIG.inputFile != 0 && CONFIG.outputDirectory !=0)
    {
        int height, width;
        pixel **array = openBMP(&height, &width);

        field *f = LifeGame(height, width, array);

        game(f);
    }
    else
    {
        if (CONFIG.inputFile == 0) printf("Input File not provided\n");
        if (CONFIG.outputDirectory == 0 ) printf("Output Directory not provided\n");
    }
}
