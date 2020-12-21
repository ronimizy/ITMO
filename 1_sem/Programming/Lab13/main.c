#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define byte sizeof(unsigned char)


void show(char *fileName, char *name)
{
    FILE *song = fopen(fileName, "rb");

    char *tag = malloc(10 * byte);
    fread(tag, byte, 10, song);

    if (strcmp(name, "all") == 0)
    {
        printf("%s", tag);
        printf("%d.%d", *(tag + 3), *(tag + 4));
        printf("%d\n", *(tag + 5));
    }

    while (1)
    {
        fread(tag, byte, 10, song);
        long long tagSize = *(tag + 7) + *(tag + 6) * 256 + *(tag + 5) * 256 * 256 + *(tag + 4) * 256 * 256 * 256;
        char tagName[5];
        tagName[0] = *tag;
        tagName[1] = *(tag + 1);
        tagName[2] = *(tag + 2);
        tagName[3] = *(tag + 3);
        tagName[4] = '\0';

        if (tagSize == 0 || strcmp(tagName, "0000") == 0) break;

        if (strcmp(name, "all") == 0 || strcmp(tagName, name) == 0)
        {
            char *value = malloc(tagSize * byte);
            printf("%s ", tag);

            printf("%d %d ", *(tag + 8), *(tag + 9));

            fread(value, byte, tagSize, song);

            for (int i = 0; i < tagSize; i++) printf("%c", *(value + i));
            printf("\n");

            free(value);
            if (strcmp(name, "all") != 0) break;
        } else fseek(song, tagSize, SEEK_CUR);
    }


    free(tag);
    fclose(song);
}

void set(char *fileName, char *name, char *value)
{
    char *tag = malloc(10 * byte);
    FILE *song = fopen(fileName, "rb");
    FILE *buffer = fopen("buffer.mp3", "w+b");
    fread(tag, byte, 10, song);
    for (int i = 0; i < 10; i++) putc(tag[i], buffer);

    long long size = *(tag + 9) + *(tag + 8) * 256 + *(tag + 7) * 256 * 256 + *(tag + 6) * 256 * 256 * 256;
    long long oldSize = 0;
    int newSize = (int) strlen(value);

    while (ftell(song) < size + 10)
    {
        fread(tag, byte, 10, song);
        char tagName[5];
        tagName[0] = *tag;
        tagName[1] = *(tag + 1);
        tagName[2] = *(tag + 2);
        tagName[3] = *(tag + 3);
        tagName[4] = '\0';

        long long tagSize = *(tag + 7) + *(tag + 6) * 256 + *(tag + 5) * 256 * 256 + *(tag + 4) * 256 * 256 * 256;

        if (tagSize == 0 || strcmp(tagName, "0000") == 0) break;

        if (strcmp(tagName, name) != 0)
        {
            fwrite(tag, byte, 10, buffer);

            int c;
            for (int i = 0; i < tagSize; i++)
            {
                c = getc(song);
                putc(c, buffer);
            }
        } else
        {
            *(tag + 7) = (char) (newSize % 256);
            *(tag + 6) = (char) (newSize / 256 % 256);
            *(tag + 5) = (char) (newSize / 256 / 256 % 256);
            *(tag + 4) = (char) (newSize / 256 / 256 / 256 % 256);

            oldSize = tagSize;

            for (int i = 0; i < 10; i++) putc(*(tag + i), buffer);
            for (int i = 0; i < newSize; i++) putc(value[i], buffer);
            fseek(song, tagSize, SEEK_CUR);
            break;
        }
    }

    long long cur = ftell(song);
    fseek(song, 0, SEEK_END);
    long long end = ftell(song);
    fseek(song, cur - end, SEEK_END);

    char *residue = malloc(byte * (end - cur) + byte);
    fread(residue, byte, end - cur, song);
    residue[end - cur] = '\0';
    fwrite(residue, byte, end - cur, buffer);

    free(residue);

    fseek(song, 0, SEEK_SET);
    fseek(buffer, 0, SEEK_SET);

    fread(tag, byte, 10, song);

    size = size - oldSize + newSize;
    *(tag + 9) = (char) (size % 256);
    *(tag + 8) = (char) (size / 256 % 256);
    *(tag + 7) = (char) (size / 256 / 256 % 256);
    *(tag + 6) = (char) (size / 256 / 256 / 256 % 256);

    for (int i = 0; i < 10; i++) putc(tag[i], buffer);

    fclose(song);
    fclose(buffer);
    remove(fileName);
    rename("buffer.mp3", fileName);

    free(tag);
}

int main(int argc, char **argv)
{
//    argv[1] = "--filepath=song.mp3";
//    argv[2] = "--show";
//    argv[2] = "--set=TRCK";
//    argv[3] = "--value=DEEG";
    int fpArgLen = (int) strlen("--filepath=");
    int pathLen = (int) strlen(argv[1]);
    int size = pathLen - fpArgLen;


    char *fileName = malloc(size + 1);

    for (int i = fpArgLen; i < pathLen; i++) fileName[i - fpArgLen] = argv[1][i];
    fileName[size] = '\0';


    //FILE *song = fopen(fileName, "r+");

    if (argv[2][2] == 's')
    {
        if (argv[2][3] == 'h') show(fileName, "all");
        else
        {
            int valueArgLen = strlen("--value=");
            int valueLen = (int) strlen(argv[3]) - valueArgLen;

            char name[5];
            name[0] = argv[2][6];
            name[1] = argv[2][7];
            name[2] = argv[2][8];
            name[3] = argv[2][9];
            name[4] = '\0';

            char *value = malloc(valueLen + 1);
            for (int i = valueArgLen; i < valueArgLen + valueLen; i++) value[i - valueArgLen] = argv[3][i];
            value[valueLen] = '\0';

            set(fileName, name, value);
            free(value);
        }
    } else
    {
        char name[5];
        name[0] = argv[2][6];
        name[1] = argv[2][7];
        name[2] = argv[2][8];
        name[3] = argv[2][9];
        name[4] = '\0';

        show(fileName, name);
    }

    //fclose(song);
    free(fileName);

    return 0;
}
