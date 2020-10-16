#include <stdio.h>

int NOD(int a, int b)
{
    if (a < b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    while (b)
    {
        a %= b;
        int tmp = a;
        a = b;
        b = tmp;
    }

    return a;
}

int NOK(int a, int b)
{
    int nod = NOD(a, b);
    return (a * b) / nod;
}

int numbersSum(a)
{
    if (a != 0)
    {
        int sum = numbersSum(a/10);
        return sum+a%10;
    }
    return 0;
}

int main()
{
    printf("Hello, World!\n");
    return 0;
}
