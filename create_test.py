#!/usr/bin/env python

import sys
import getopt
import numpy as np
from scipy.io import mmwrite

def usage():
    sys.stderr.write("Usage: {} [options] -m <number of rows> -n <number of columns> -r <rank> -o <matrix file> -s <singular values file>\n".format(sys.argv[0]))
    sys.stderr.write("Options: -d, --dominant-value FLOAT    the dominant singular value (default: 100.0)\n")
    sys.stderr.write("         -a, --damping FLOAT           the damping factor (default: 2.0)\n")
    sys.stderr.write("         -h, --help                    print this help message\n")
    sys.exit(1)

def gen_svd_test(nrows, ncols, rank, dom_sval, damping):
    assert nrows >= ncols and rank <= ncols
    U, _ = np.linalg.qr(np.random.random((nrows, nrows))) # random m-by-m orthogonal matrix U
    V, _ = np.linalg.qr(np.random.random((ncols, ncols))) # random n-by-n orthogonal matrix V
    S = np.zeros((nrows, ncols), dtype=np.float64)
    S[0,0] = dom_sval
    for i in range(1, rank): S[i,i] = S[i-1,i-1] / damping
    A = U@S@V.T
    U = U[:,:ncols]
    S = S[:ncols,:ncols]
    return A, U, S, V

if __name__ == "__main__":
    try: opts, args = getopt.getopt(sys.argv[1:], "m:n:r:o:s:d:a:h", ["dominant-value=", "damping=", "help"])
    except getopt.GetoptError as err:
        sys.stderr.write("{}\n".format(err))
        usage()

    nrows, ncols, rank, mat_file, sval_file = None, None, None, None, None
    dom_sval, damping = 100.0, 2.0

    for o, a in opts:
        if o == "-m": nrows = int(a)
        elif o == "-n": ncols = int(a)
        elif o == "-r": rank = int(a)
        elif o == "-o": mat_file = a
        elif o == "-s": sval_file = a
        elif o in ("-d", "--dominant-value"): dom_sval = float(a)
        elif o in ("-a", "--damping"): damping = float(a)
        elif o in ("-h", "--help"): usage()
        else: assert False, "unhandled option"

    if nrows is None or ncols is None or rank is None or mat_file is None or sval_file is None:
        sys.stderr.write("Missing required arguments\n")
        usage()

    A, U, S, V = gen_svd_test(nrows, ncols, rank, dom_sval, damping)
    mmwrite(mat_file, A)
    np.savetxt(sval_file, np.diag(S), fmt="%.18e")

    sys.exit(0)
