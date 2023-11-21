#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "svd_routines.h"
#include "kiss.h"

int main(int argc, char *argv[])
{
    size_t m = 100;
    size_t n = 20;
    double *A = malloc(m*n*sizeof(double));

    kiss_init();

    for (size_t i = 0; i < m*n; ++i) A[i] = kiss_unirandf();

    serial_thin_lapack_svd_values(A, NULL, m, n);


    return 0;
}

