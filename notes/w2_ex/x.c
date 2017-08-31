#include <stdio.h>

int main(void)
{
    double *r = (double *)0x6060;
    r += 2;
    printf("%d %p\n", (int)r % 8, r);
    return 0;
}
