//
// Created by Георгий Круглов on 17.11.2020.
//

#ifndef LAB14_COLOR_H
#define LAB14_COLOR_H

typedef struct rgb_pixel PIXEL;

struct rgb_pixel
{
    int blue;
    int green;
    int red;
};

PIXEL** scale(PIXEL** in, int scale, int h, int w)
{
    PIXEL** r = calloc(h * scale, sizeof(PIXEL*));
    for (int i = 0; i < h*scale; i++) r[i] = calloc(w*scale, sizeof(PIXEL));

    for (int height = 0; height < h; height++)
    {
        for (int sH = 0; sH < scale; sH++)
        {
            for (int width = 0; width < w; width++)
            {
                for (int sW = 0; sW < scale; sW++)
                {
                    r[height+sH][width+sW] = in[height][width];
                }
            }
        }
    }

    return r;
}

PIXEL Black()
{
    PIXEL p;
    p.red = 0;
    p.green = 0;
    p.blue = 0;

    return p;
}

PIXEL White()
{
    PIXEL p;
    p.red = 255;
    p.green = 255;
    p.blue = 255;

    return p;
}

typedef struct lifeGameColorScheme scheme;

struct lifeGameColorScheme
{
    PIXEL dead;
    PIXEL alive;
};

scheme Light()
{
    scheme s;
    s.alive = Black();
    s.dead = White();

    return s;
}

scheme Dark()
{
    scheme s;
    s.alive = White();
    s.dead = Black();

    return s;
}

#endif //LAB14_COLOR_H
