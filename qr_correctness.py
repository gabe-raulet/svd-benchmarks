#!/usr/bin/env python

import sys
import getopt
import numpy as np
from scipy.io import mmread
from pathlib import Path

abstol = 1e-5

def usage():
    global abstol
    sys.stderr.write(f"Usage: {sys.argv[0]} -i <directory with computed Q.mtx and R.mtx> -A <input A.mtx>\n")
    sys.stderr.write("Options: -v        verbose\n")
    sys.stderr.write(f"         -e FLOAT  absolute tolerance (default: {abstol:.2e})\n")
    sys.stderr.write("         -h        help message\n")
    sys.stderr.flush()
    sys.exit(1)

def report(correct):
    if correct: sys.stdout.write("Correct\n")
    else: sys.stdout.write("Incorrect\n")
    sys.exit(0)

if __name__ == "__main__":
    correctdir, matfile, verbose = None, None, False
    try: opts, args = getopt.getopt(sys.argv[1:], "i:A:e:vh")
    except getopt.GetoptError as err: usage()

    for o, a in opts:
        if o == "-i": correctdir = a
        elif o == "-A": matfile = a
        elif o == "-v": verbose = True
        elif o == "-e": abstol = float(a)
        elif o == "-h": usage()
        else: assert False, "unhandled option"

    if correctdir is None: usage()
    correctpath = Path(correctdir)
    if not correctpath.exists():
        sys.stderr.write(f"Error: '{str(correctpath)}' does not exist\n")
        sys.stderr.flush()
        sys.exit(1)

    Qpath = correctpath.joinpath("Q.mtx")
    Rpath = correctpath.joinpath("R.mtx")

    if not Qpath.is_file() or not Rpath.is_file():
        sys.stderr.write(f"Error: '{str(correctpath)}' must contain Q.mtx and/or R.mtx\n")
        sys.stderr.flush()
        sys.exit(1)

    matpath = Path(matfile)
    if not matpath.is_file():
        sys.stderr.write(f"Error: '{str(matpath)}' is does not exist\n")
        sys.stderr.flush()
        sys.exit(1)

    A = mmread(str(matpath))
    Q = mmread(str(Qpath))
    R = mmread(str(Rpath))

    m, n = A.shape
    if Q.shape != A.shape:
        if verbose: sys.stderr.write("A and Q have mismatching dimension\n")
        report(False)

    if R.shape[0] != R.shape[1]:
        if verbose: sys.stderr.write("R is not square\n")
        report(False)

    if R.shape[0] != n:
        if verbose: sys.stderr.write("R has different number of columns than A\n")
        report(False)

    if not np.allclose(R, np.triu(R)):
        if verbose: sys.stderr.write("R is not upper triangular\n")
        report(False)

    I = np.eye(n, dtype=A.dtype)
    orthodiff = np.linalg.norm(I-Q.T@Q, ord="fro")

    if orthodiff > abstol:
        if verbose: sys.stderr.write(f"norm(I - Q^T*Q)={orthodiff:.5e} > abstol={abstol:.5e} -> Q doesn't have orthonormal columns\n")
        report(False)

    Adiff = np.linalg.norm(A-Q@R, ord="fro")
    if Adiff > abstol:
        if verbose: sys.stderr.write(f"norm(A - Q*R)={Adiff:.5e} > abstol={abstol:.5e} -> Q*R != A\n")
        report(False)

    report(True)
