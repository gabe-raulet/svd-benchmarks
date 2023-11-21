#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "linalg_routines.h"
#include "mmio_dense.h"
#include "kiss.h"

int init_random_matrix(double **A_ref, int m, int n);

int main(int argc, char *argv[])
{
    kiss_init();

    FILE *f;
    int m, n;
    double *A, *Q, *R;

    m = 15;
    n = 10;
    init_random_matrix(&A, m, n);

    f = fopen("A.mtx", "w");
    mmio_write_dense(f, A, m, n, 0);
    fclose(f);

    serial_qr_lapack(A, &Q, &R, m, n);

    f = fopen("R.mtx", "w");
    mmio_write_dense(f, R, n, n, 0);
    fclose(f);

    f = fopen("Q.mtx", "w");
    mmio_write_dense(f, Q, m, n, 0);
    fclose(f);

    return 0;
}

int init_random_matrix(double **A_ref, int m, int n)
{
    assert(A_ref != NULL && m >= 1 && n >= 1);

    double *A = malloc(m*n*sizeof(double));
    assert(A != NULL);

    for (int i = 0; i < m*n; ++i)
        A[i] = kiss_unirandf();

    *A_ref = A;
    return 0;
}
