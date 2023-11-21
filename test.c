#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "svd_routines.h"
#include "mmio.h"
#include "kiss.h"

int main(int argc, char *argv[])
{

    MM_typecode matcode;
    int m, n;
    FILE *fp = fopen("A.mtx", "r");

    mm_read_banner(fp, &matcode);
    assert(mm_is_dense(matcode));

    mm_read_mtx_array_size(fp, &m, &n);

    double *A = malloc(m*n*sizeof(double));

    /*
     * REMEMBER: matrix market stores dense matrices in COLUMN MAJOR order.
     */
    for (int i = 0; i < m*n; ++i)
        fscanf(fp, "%lg", &A[i]);

    fclose(fp);

    double *SIGMA, *U, *Vt;

    serial_thin_lapack_svd(A, &SIGMA, &U, &Vt, m, n);

    int p = m < n? m : n;
    for (int i = 0; i < p; ++i)
    {
        printf("%.18e\n", SIGMA[i]);
    }

    return 0;
}

