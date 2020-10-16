#include <stdio.h>
#include <math.h>

enum OSs {
    Symbian = 1, EmbeddedLinux, WindowsCE, VxWorks, QNX
} OS;

typedef struct circle {
    double centerX;
    double centerY;

    double radius;
} CIRCLE;

union keyboard {
    unsigned int numLock: 1;
    unsigned int capsLock: 1;
    unsigned int scrollLock: 1;
};

double circleLength(CIRCLE circle) {
    return 2 * M_PI * circle.radius;
}


int main() {

    enum OSs sy = Symbian;
    CIRCLE circle;
    union keyboard keyboard;
    circle.radius = 20;

    printf("OS: %d\n", sy);
    printf("Circle Length: %f\n", circleLength(circle));

    scanf("%x", &keyboard);
    printf("NumLock: %s\nCapsLock: %s\nScrollLock: %s\n",
           keyboard.numLock == (unsigned) 1 ? "ON" : "OFF",
           keyboard.capsLock == (unsigned) 1 ? "ON" : "OFF",
           keyboard.scrollLock == (unsigned) 1 ? "ON" : "OFF");

    return 0;
}
