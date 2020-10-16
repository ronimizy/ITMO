#include <iostream>
#include <cmath>
#include "bitmap_image.hpp"                                // библиотека, обрабатывающая изображения

using namespace std;

int main()
{
    int a[128][128];                                       // массив для хранения цветов изображения
    bitmap_image image("image_128.bmp");
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            rgb_t color;                                   // структура, в которой хранятся значения хар-ки цветов
            image.get_pixel(x, y, color.red, color.green, color.blue);
            a[x][y] = color.red;
        }
    }

    for (int i = 0; i < 128; i++)
        cout << a[i][64] << ' ';                           // вывод средней строки изображения
    cout << endl;

    int b[261] = {0};
    for (int i = 0; i < 128; i++)
    {
        a[i][64] = (int)round(double(a[i][64]) / 20) * 20;      // квантование средней строки изображения
        b[a[i][64]]++;
        cout << a[i][64] << ' ';                           // вывод отквантованной средней строки изображения
    }
    cout << endl;

    double e = 0;                                                     // энтропия
    for (int i = 0; i < 261; i++)
    {
        if (b[i] > 0)
        {
            cout << i << ' ' << b[i] << endl;
            e = e - (double(b[i]) / 128) * log2(double(b[i]) / 128); //подсчет энтропии
        }
    }
    cout << e;                                                       //вывод значения энтропии
    return 0;
}