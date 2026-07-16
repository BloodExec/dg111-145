#include <stdio.h>
#include <math.h>
int main()
{
    // 1.1
    int a;
    a = 10 / 3;
    printf("a = %d\n", a);

    float b;
    b = 10.0 / 3;
    printf("b = %f\n", b);

    float c;
    c = (float)10 / 3;
    printf("c = %f\n", c);

    int d;
    d = 10 % 3;
    printf("d = %d\n", d);

    int f;
    f = -7 % 3;
    printf("f = %d\n", f);

    int g;
    g = 7 % -3;
    printf("g = %d\n", g);

    // 1.2
    int x = 5;
    printf("x++ = %d\n", x++);
    printf("x = %d\n", x);
    x = 5;
    printf("++x = %d\n", ++x);
    printf("x = %d\n", x);

    // 1.3
    printf("2 + 3 * 4 = %d\n", 2 + 3 * 4);
    printf("(2 + 3) * 4 = %d\n", (2 + 3) * 4);
    printf("10 - 2 - 3 = %d\n", 10 - 2 - 3);
    printf("2*3 + 4*5 = %d\n", 2 * 3 + 4 * 5);

    return 0;
}