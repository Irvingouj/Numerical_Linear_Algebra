#include <stdio.h>
#include "include/matrix.h"

int main(int argc, char const *argv[])
{
    Matrix Matrix;

    double value[] = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    Matrix_init(&Matrix,3,3);
    Matrix_destroy(&Matrix);
    return 0;
}
