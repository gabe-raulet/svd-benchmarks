import numpy as np
from scipy.linalg.lapack import dgesvd

# Example matrix
A = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=np.float64)

# Get matrix dimensions
m, n = A.shape

# Initialize arrays for the singular values, left singular vectors, right singular vectors
U = np.empty((m, m), dtype=np.float64)
Vt = np.empty((n, n), dtype=np.float64)
singular_values = np.empty(min(m, n), dtype=np.float64)

# Call LAPACK's dgesvd function
u, s, vt, info = dgesvd(A, compute_uv=0)

# Check the info value for success (0 means successful computation)
if info >= 0:
    print("Singular values:", s)
else:
    print("SVD computation failed.")
