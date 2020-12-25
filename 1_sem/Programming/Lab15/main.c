#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

#include "EncodingDecoding.h"

typedef struct {
    UC typeFlag[4];

    UC *fileCount; //4 байта

    UC **fileNamesSizes; //один size 4 байта
    UC **fileNames;

    UC **filesSizes; //один size 4 байта
    UC **files;
} ARC;


//Определение длины файла
ULL filesize(UC *fileName) {
    FILE *f;
    if ((f = fopen((char *) fileName, "rb")) == NULL) {
        printf("Failed to open a file %s", fileName);
        exit(__LINE__);
    }

    fseek(f, 0, SEEK_END);
    ULL size = ftell(f);

    fclose(f);
    return size;
}

UC *getContentsOfFile(UC *fileName, ULL size) {
    UC *contents = calloc(size + 1, sizeof(UC));
    FILE *f;
    if ((f = fopen((char *) fileName, "rb")) == NULL) {
        printf("Failed to open a file %s", fileName);
        exit(__LINE__);
    }

    fread(contents, sizeof(UC), size + 1, f);
    contents[size] = '\0';

    return contents;
}

//Перевод числа в его 16-ти ричное представление Little-Endian
UC *dtoxc(ULL a) {
    UC *c = calloc(5, sizeof(char));

    for (ULL i = 0; i < 4; i++) {
        c[i] = (char) a % 256;
        a /= 256;
    }
    c[4] = '\0';

    return c;
}

//Перевод 16-ти ричного Little-Endian представления числа
ULL xctod(const UC c[5]) {
    ULL a = 0;

    for (ULL i = 0; i < 4; i++) {
        a += ((ULL) c[i]) * (ULL) pow(256, i);
    }

    return a;
}

//Извлечение имени файла, без полного пути
UC *getFileName(UC *fileName) {
    ULL length = strlen((char *) fileName);
    ULL size = 0;

    //––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\\
    //НЕ ТРОГАТЬ ЛОНГИ, ЕСЛИ СДЕЛАТЬ ULL БУДЕТ БЕСКОНЕЧНЫЙ ЦИКЛ!!!!!!!!!!!!!!!!!|||
    //––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––//

    UC *reversed = calloc(length, sizeof(UC));
    for (long i = (long) length - 1; i >= 0; i--) {
        if (fileName[i] == '/') break;
        reversed[size++] = fileName[i];
    }

    length = 0;
    UC *cut = calloc(size + 1, sizeof(UC));
    for (long i = (long) size - 1; i >= 0; i--)
        cut[length++] = reversed[i];

    cut[size] = '\0';

    return cut;
}

//Сложение директории и имени файла
UC *fileAtDirectory(UC *directory, UC *file) {
    UC *path = calloc(strlen((char *) directory) + strlen((char *) file), sizeof(UC));

    strcpy((char *) path, (char *) directory);
    strcat((char *) path, (char *) file);

    return path;
}

void freeARC(ARC *archive) {
    ULL fileCount = xctod(archive->fileCount);

    free(archive->fileCount);

    for (ULL i = 0; i < fileCount; i++) {
        free(archive->fileNamesSizes[i]);
        free(archive->fileNames[i]);
        free(archive->filesSizes[i]);
        free(archive->files[i]);
    }
    free(archive->fileNamesSizes);
    free(archive->fileNames);
    free(archive->filesSizes);
    free(archive->files);
}

void createArc(ULL fileCount, UC **fileNames, UC *outputName) {

    //Создание и заполнение контейнера
    ARC archive;
    strcpy((char *) archive.typeFlag, "ARC\0");

    archive.fileCount = dtoxc(fileCount);

    archive.fileNamesSizes = calloc(fileCount, sizeof(UC *));
    archive.fileNames = calloc(fileCount, sizeof(UC *));

    archive.filesSizes = calloc(fileCount, sizeof(UC *));
    archive.files = calloc(fileCount, sizeof(UC *));

    for (ULL i = 0; i < fileCount; i++) {
        archive.fileNames[i] = getFileName(fileNames[i]);
        archive.fileNamesSizes[i] = dtoxc(strlen((char *) archive.fileNames[i]));

        ULL size = filesize(fileNames[i]);
        archive.files[i] = getContentsOfFile(fileNames[i], size);
        archive.filesSizes[i] = dtoxc(size);
    }

    //Запись контейнера в файл
    FILE *a = fopen((char *) outputName, "wb");

    fwrite(archive.typeFlag, sizeof(char), 3, a);

    fwrite(archive.fileCount, sizeof(char), 4, a);

    //Запись длин файлов и их имён
    for (ULL i = 0; i < fileCount; i++) {
        ULL size = xctod(archive.fileNamesSizes[i]);
        fwrite(archive.fileNamesSizes[i], sizeof(char), 4, a);
        fwrite(archive.fileNames[i], sizeof(char), size, a);
    }

    //Запись длины файла и его контента
    for (ULL i = 0; i < fileCount; i++) {
        ULL size = xctod(archive.filesSizes[i]);
        fwrite(archive.filesSizes[i], sizeof(char), 4, a);
        fwrite(archive.files[i], sizeof(char), size, a);

        printf(" ");
    }

    fclose(a);

    //Очистка памяти
    freeARC(&archive);

    encode(outputName);
}

void unpackArc(UC *inputName, UC *outputDirectory) {
    decode(inputName);

    //Создание и подготовка контейнера
    ARC archive;

    archive.fileCount = calloc(5, sizeof(UC));

    FILE *a;
    if ((a = fopen((char *) inputName, "rb")) == NULL) {
        printf("Failed to open an .arc file\n");
        exit(__LINE__);
    }

    //Заполнение контейнера информацией из файла
    fread(archive.typeFlag, sizeof(UC), 3, a);
    archive.typeFlag[3] = '\0';
    if (strcmp((const char *) archive.typeFlag, "ARC\0") != 0) {
        printf("Given file is not .arc\n");
        exit(__LINE__);
    }

    fread(archive.fileCount, sizeof(UC), 4, a);
    archive.fileCount[4] = '\0';

    ULL filesCount = xctod(archive.fileCount);

    //Заполнение имён файлов
    archive.fileNamesSizes = calloc(filesCount, sizeof(UC *));
    archive.fileNames = calloc(filesCount, sizeof(UC *));
    for (ULL i = 0; i < filesCount; i++) {
        archive.fileNamesSizes[i] = calloc(5, sizeof(UC));
        archive.fileNamesSizes[i][4] = '\0';

        fread(archive.fileNamesSizes[i], sizeof(UC), 4, a);
        ULL size = xctod(archive.fileNamesSizes[i]);

        archive.fileNames[i] = calloc(size + 1, sizeof(UC));
        archive.fileNames[i][size] = '\0';

        fread(archive.fileNames[i], sizeof(UC), size, a);
    }

    //Заполнение данных файлов
    archive.filesSizes = calloc(filesCount, sizeof(UC *));
    archive.files = calloc(filesCount, sizeof(UC *));
    for (ULL i = 0; i < filesCount; i++) {
        archive.filesSizes[i] = calloc(5, sizeof(UC));
        archive.filesSizes[i][4] = '\0';

        fread(archive.filesSizes[i], sizeof(UC), 4, a);
        ULL size = xctod(archive.filesSizes[i]);

        archive.files[i] = calloc(size + 1, sizeof(UC));
        archive.files[i][size] = '\0';

        fread(archive.files[i], sizeof(UC), size, a);
    }

    //Добавление директории к файлам
    for (ULL i = 0; i < filesCount; i++) archive.fileNames[i] = fileAtDirectory(outputDirectory, archive.fileNames[i]);

    mkdir((char *) outputDirectory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    //Запись файлов
    for (ULL i = 0; i < filesCount; i++) {
        FILE *f;
        if ((f = fopen((char *) archive.fileNames[i], "wb")) == NULL) {
            printf("Failed to create unpacking file %s\n", archive.fileNames[i]);
            exit(__LINE__);
        }

        ULL size = xctod(archive.filesSizes[i]);

        fwrite(archive.files[i], sizeof(UC), size, f);
        fclose(f);
    }

    fclose(a);

    //Очистка памяти
    freeARC(&archive);

    encode(inputName);
}

void arcList(UC *inputName) {
    //Создание и подготовка контейнера

    FILE *a;
    if ((a = fopen((char *) inputName, "rb")) == NULL) {
        printf("Failed to open an .arc file\n");
        exit(__LINE__);
    }

    //Заполнение контейнера информацией из файла
    UC flag[4] = {'\0'};
    fread(flag, sizeof(UC), 3, a);
    if (strcmp((const char *) flag, "ARC\0") != 0) {
        printf("Given file is not .arc\n");
        exit(__LINE__);
    }

    UC fileCountC[5] = {'\0'};
    fread(fileCountC, sizeof(UC), 4, a);

    ULL filesCount = xctod(fileCountC);

    //Заполнение имён файлов
    for (ULL i = 0; i < filesCount; i++) {
        UC sizeC[5] = {'\0'};

        fread(sizeC, sizeof(UC), 4, a);
        ULL size = xctod(sizeC);

        UC *name = calloc(size + 1, sizeof(UC));
        name[size] = '\0';

        fread(name, sizeof(UC), size, a);

        printf("%s\n", name);

        free(name);
    }
}

typedef enum {
    create,
    unpack,
    list
} TASK;


int main(int argc, char **argv) {

#define debugE

#ifdef debugC
    argc = 9;
    argv[1] = "--file";
    argv[2] = "hive.arc";
    argv[3] = "--create";
    argv[4] = "1.bmp";
    argv[5] = "2.bmp";
    argv[6] = "3.bmp";
    argv[7] = "HW_2.docx";
    argv[8] = "abc.txt";
#endif

#ifdef debugCS
    argc = 5;
    argv[1] = "--file";
    argv[2] = "hive.arc";
    argv[3] = "--create";
    argv[4] = "1.bmp";
#endif

#ifdef debugE
    argc = 5;
    argv[1] = "--file";
    argv[2] = "hive.arc";
    argv[3] = "--extract";
    argv[4] = "a/";
#endif

#ifdef debugL
    argc = 4;
    argv[1] = "--file";
    argv[2] = "hive.arc";
    argv[3] = "--list";
#endif

    TASK toDo = 100;
    UC *inputName = 0;
    UC **fileNames = 0;
    UC *outputName = 0;

    ULL fileCount = 0;

//    UC a[] = "a/1.bmp\0";
//
//    encode((UC *) &a);
//    decode((UC *) &a);

//    UC* test = malloc(3 * sizeof(UC));
//    test[0] = '5';
//    test[1] = '1';
//    test[2] = '5';
//    ULL size = 3;
//    printf("%d\n", size);
//    test = encode(test, &size);
//    printf("%d\n", size);
//    UC *nText = decode(test, &size);
//    printf("%d\n", size);
//    printf("%d\n", test[0]);
//    printf("%d\n", test[1]);
//    printf("%d\n", test[2]);

    for (int i = 1; i < argc; i++) {
        if (strcmp("--file", argv[i]) == 0) {
            ULL size = strlen(argv[i + 1]);
            inputName = calloc(size + 1, sizeof(UC));
            inputName[size] = '\0';

            strcpy((char *) inputName, argv[i + 1]);
            i++;
        } else if (strcmp("--create", argv[i]) == 0) {
            fileNames = calloc(argc - i, sizeof(UC *));
            toDo = create;

            for (int j = i + 1; j < argc; j++) {
                ULL size = strlen(argv[j]);
                fileNames[fileCount] = calloc(size + 1, sizeof(UC));
                strcpy((char *) fileNames[j - i - 1], argv[j]);
                fileNames[fileCount++][size] = '\0';
            }

            i = argc;
        } else if (strcmp("--extract", argv[i]) == 0) {
            ULL size = strlen(argv[i + 1]);
            outputName = calloc(size + 1, sizeof(UC));
            strcpy((char *) outputName, argv[i + 1]);
            outputName[size] = '\0';

            toDo = unpack;
        } else if (strcmp("--list", argv[i]) == 0) {
            toDo = list;
        }
    }

    if (toDo == create) {
        if (inputName == 0) {
            printf("Input file not provided\n");
            return 0;
        }
        if (fileNames == 0) {
            printf("Files not provided\n");
            return 0;
        }

        printf("Archiving in process...\n");
        createArc(fileCount, fileNames, inputName);
        printf("Archiving finished!\n");
    } else if (toDo == unpack) {
        if (inputName == 0) {
            printf("Input file not provided\n");
            return 0;
        }
        if (outputName == 0) {
            printf("Output directory not provided\n");
            return 0;
        }

        printf("Unpacking in process...\n");
        unpackArc(inputName, outputName);
        printf("Unpacking finished!\n");
    } else if (toDo == list) {
        arcList(inputName);
    } else {
        printf("Nothing to do...\n");
    }


    return 0;
}