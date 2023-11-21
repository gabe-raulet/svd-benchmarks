#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "svd_routines.h"
#include "mmio_dense.h"
#include "kiss.h"

int main(int argc, char *argv[])
{
    FILE *f;
    int m, n;
    double *A, *SIGMA, *U, *Vt;

    f = fopen("A.mtx", "r");
    mmio_read_dense(f, &A, &m, &n, 0);
    fclose(f);
    serial_thin_lapack_svd(A, &SIGMA, &U, &Vt, m, n);

    f = fopen("U.mtx", "w");
    mmio_write_dense(f, U, m, n, 0);
    fclose(f);

    f = fopen("Vt.mtx", "w");
    mmio_write_dense(f, Vt, m, n, 0);
    fclose(f);

    free(A);
    free(SIGMA);
    free(U);
    free(Vt);

    return 0;
}

