#ifndef LINALG_ROUTINES_H_
#define LINALG_ROUTINES_H_

int serial_thin_lapack_svd(double *A, double **SIGMA_ref, double **U_ref, double **Vt_ref, int m, int n);

#endif
