#ifndef SVD_ROUTINES_H_
#define SVD_ROUTINES_H_

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "lapacke.h"

#define min(a, b) (((a) < (b))? (a) : (b))
#define max(a, b) (((a) > (b))? (a) : (b))


    /*
     * DGESVD computes the SVD of a real m-by-n matrix A = U * SIGMA * transpose(V).
     *
     * jobu:
     *      'A': all m columns of U are returned in array U
     *      'S': the first min(m,n) columns of U (the left singular vectors) are returned in the array U
     *      'N': no columns of U are computed
     *
     *  jobvt:
     *      'A': all n rows of V^T are returned in the array vt.
     *      'S': the first min(m,n) rows ov V^T (the right singular vectors) are returned in the array VT.
     *      'N': no rows of V&T are computed.
     *
     *  m: number of rows of the input matrix A.
     *
     *  n: number of columns of the input matrix A.
     *
     *  A: double precision array, dimension (lda,n). On entry, the m-by-n matrix.
     *
     *  lda: the leading dimension of the array A. lda >= max(1,m).
     *
     *  s: double precision array, dimension (min(m,n)). The singular vales of A, sorted so that s(i) >= s(i+1).
     *
     *  u: double precision array, dimension (ldu,m) if jobu='A' or (ldu,min(m,n)) if jobu='S'.
     *     If jobu='A', U contains the m-by-m orthogonal matrix U;
     *     If jobu='S', U contains the first min(m,n) columns of U (the left singular vectors, stored columnwise);
     *
     *  ldu: The leading dimension of the array U. ldu >= 1; if jobu='S' or jobu='A', ldu >= m.
     *
     *  vt: double precision array, dimension (ldvt,n).
     *      If jobvt = 'A', vt contains the n-by-n orthogonal matrix V^T.
     *      if jobvt = 'S', vt contains the first min(m,n) rows of V^T (the right singular vectors, stored rowwise).
     *
     *  ldvt: the leading dimension of the array vt. ldvt >= 1; if jobvt = 'A', ldvt >= n; if jobvt = 'S', ldvt >= min(m,n).
     *
     *  work: work is double precision array,dimension (max(1,lwork))
     *
     *  lwork: dimension of the array work. lwork >= max(1,5*min(m,n)).
     *
     */

int serial_thin_lapack_svd_values(double *A, double *svals, size_t m, size_t n)
{
    size_t lda = m;
    size_t ldu = 1;
    size_t ldvt = 1;
    size_t lwork = 5 * min(m,n);
    double *s = malloc(min(m,n) * sizeof(double));
    double *work = malloc(lwork * sizeof(double));

    LAPACKE_dgesvd(LAPACK_ROW_MAJOR, 'N', 'N', m, n, A, lda, s, NULL, ldu, NULL, ldvt, work);

    return 0;
}

#endif
