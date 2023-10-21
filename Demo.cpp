#include <stdio.h>
#include <stdlib.h>

#include "config.h"

#ifdef USE_MYMATH
    #include "MathFunction.h"
#else
    #include <math.h>
#endif

int main(int argc, char *argv[])
{
    printf("The version is %d.%d\n", DEMO_VERSION_MAJOR, DEMO_VERSION_MINOR);
    if (argc < 3) {
        printf("Usage: %s has no enough parameters", argv[0]);
        return 1;
    }
    int base = atoi(argv[1]);
    int index = atoi(argv[2]);

    int result;
#ifdef USE_MYMATH
    printf("Now we use our own math library\n");
    result = Exponent(base, index);
#else
    printf("Now we use the standard library\n");
    result = pow(base, index);
#endif

    printf("%d^%d=%d\n", base, index, result);
    return 0;
}