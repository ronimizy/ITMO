#include <stdio.h>
#include "isosceles_triangle.h"

int main()
{
    ISOSCELESTRIANGLE triangle = readTriangle();
    printf("\nПериметр треугольника: %lf", findPerimeter(triangle));
    printf("\nПлощадь треугольника: %lf", findAreaSize(triangle));

    return 0;
}
