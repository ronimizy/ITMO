#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    freopen("output.txt", "w", stdout);
    int a = (int)strtol(argv[1], NULL, 10);
    int b = (int)strtol(argv[2], NULL, 10);
    printf("%d", a+b);

    return 0;
}