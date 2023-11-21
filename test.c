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
    /*size_t m = 100;*/
    /*size_t n = 20;*/
    /*double *A = malloc(m*n*sizeof(double));*/

    /*kiss_init();*/

    /*for (size_t i = 0; i < m*n; ++i) A[i] = kiss_unirandf();*/

    MM_typecode matcode;
    int mi, ni;
    FILE *fp = fopen("A.mtx", "r");

    mm_read_banner(fp, &matcode);
    assert(mm_is_dense(matcode));

    mm_read_mtx_array_size(fp, &mi, &ni);

    double *A = malloc(mi*ni*sizeof(double));

    for (int i = 0; i < mi*ni; ++i)
        fscanf(fp, "%lg", &A[i]);

    fclose(fp);

    int p = mi < ni? mi : ni;
    double *svals = malloc(p * sizeof(double));

    serial_thin_lapack_svd_values(A, svals, (size_t)mi, (size_t)ni);


    for (int i = 0; i < p; ++i)
    {
        printf("%.18e\n", svals[i]);
    }

    return 0;
}
