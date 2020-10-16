//
// Created by Георгий Круглов on 11.10.2020.
//

#include <stdio.h>
#include <math.h>

#ifndef LAB11_ISOSCELES_TRIANGLE_H
#define LAB11_ISOSCELES_TRIANGLE_H

typedef struct point
{
    double x,y;
}POINT;

typedef struct IsoscelesTriangle
{
    POINT a;
    POINT b;
    POINT c;
}ISOSCELESTRIANGLE;

double findEdgeLength(POINT a, POINT b)
{
    double xLength = a.x - b.x, yLength = a.y - b.y;
    return pow((pow(xLength, 2) + pow(yLength, 2)), 0.5);
}

double findPerimeter(ISOSCELESTRIANGLE triangle)
{
    return findEdgeLength(triangle.a, triangle.b) + findEdgeLength(triangle.b, triangle.c) + findEdgeLength(triangle.a, triangle.c);
}

double findAreaSize(ISOSCELESTRIANGLE triangle)
{
    double halfPerimeter = findPerimeter(triangle)/2;
    double a = findEdgeLength(triangle.c, triangle.b);
    double b = findEdgeLength(triangle.a, triangle.c);
    double c = findEdgeLength(triangle.a, triangle.b);

    return pow(halfPerimeter*(halfPerimeter-a)*(halfPerimeter-b)*(halfPerimeter-c), 0.5);
}

ISOSCELESTRIANGLE readTriangle()
{
    POINT a, b, c;
    printf("Введите первую точку треугольника: \n");
    printf("\tx:"); scanf("%lf", &a.x);
    printf("\ty:"); scanf("%lf", &a.y);

    printf("Введите вторую точку треугольника: \n");
    printf("\tx:"); scanf("%lf", &b.x);
    printf("\ty:"); scanf("%lf", &b.y);

    printf("Введите третью точку треугольника: \n");
    printf("\tx:"); scanf("%lf", &c.x);
    printf("\ty:"); scanf("%lf", &c.y);

    ISOSCELESTRIANGLE triangle;
    triangle.a = a;
    triangle.b = b;
    triangle.c = c;

    return triangle;
}

#endif //LAB11_ISOSCELES_TRIANGLE_H
