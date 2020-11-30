//
// Created by Георгий Круглов on 17.11.2020.
//

#ifndef LAB14_COLOR_H
#define LAB14_COLOR_H

typedef struct rgb_pixel pixel;

struct rgb_pixel
{
    int blue;
    int green;
    int red;
};

pixel** scale(pixel** in, int scale, int h, int w)
{
    pixel** r = calloc(h*scale, sizeof(pixel*));
    for (int i = 0; i < h*scale; i++) r[i] = calloc(w*scale, sizeof(pixel));

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

pixel Black()
{
    pixel p;
    p.red = 0;
    p.green = 0;
    p.blue = 0;

    return p;
}

pixel White()
{
    pixel p;
    p.red = 255;
    p.green = 255;
    p.blue = 255;

    return p;
}

typedef struct lifeGameColorScheme scheme;

struct lifeGameColorScheme
{
    pixel dead;
    pixel alive;
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
