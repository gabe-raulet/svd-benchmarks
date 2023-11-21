#include "mmio_dense.h"
#include "mmio.h"
#include <stdlib.h>
#include <assert.h>

int mmio_read_dense(FILE *f, double **A_ref, int *M, int *N, int row_major)
{
    assert(f != NULL && A_ref != NULL && M != NULL && N != NULL);

    MM_typecode matcode;
    int m, n, i, j;
    double *A;

    mm_read_banner(f, &matcode);
    assert(mm_is_dense(matcode));
    mm_read_mtx_array_size(f, &m, &n);
    A = malloc(m*n*sizeof(double));
    assert(A != NULL);

    if (!row_major)
    {
        for (i = 0; i < m*n; ++i)
            fscanf(f, "%lg", &A[i]);
    }
    else
    {
        for (j = 0; j < n; ++j)
            for (i = 0; i < m; ++i)
                fscanf(f, "%lg", &A[i*n + j]);
    }

    *A_ref = A;
    *M = m;
    *N = n;

    return 0;
}

int mmio_write_dense(FILE *f, double const *A, int m, int n, int row_major)
{
    assert(f != NULL && A != NULL && m >= 1 && n >= 1);

    MM_typecode matcode;
    int i, j;

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_dense(&matcode);
    mm_set_real(&matcode);
    mm_set_general(&matcode);

    mm_write_banner(f, matcode);
    fprintf(f, "%%\n");
    mm_write_mtx_array_size(f, m, n);

    if (!row_major)
    {
        for (i = 0; i < m*n; ++i)
            fprintf(f, "%.18e\n", A[i]);
    }
    else
    {
        for (j = 0; j < n; ++j)
            for (i = 0; i < m; ++i)
                fprintf(f, "%.18e\n", A[i*n + j]);
    }

    return 0;
}
