#!/usr/bin/env python

import sys
import getopt
import numpy as np
from scipy.io import mmwrite
from pathlib import Path

def usage():
    sys.stderr.write(f"Usage: {sys.argv[0]} [options] -m <number of rows> -n <number of columns> -o <output directory>\n")
    sys.stderr.write("Options: -h      help message\n")
    sys.stderr.flush()
    sys.exit(1)

if __name__ == "__main__":
    m, n, outdir = None, None, None
    try: opts, args = getopt.getopt(sys.argv[1:], "m:n:o:h")
    except getopt.GetoptError as err: usage()

    for o, a in opts:
        if o == "-m": m = int(a)
        elif o == "-n": n = int(a)
        elif o == "-o": outdir = a
        elif o == "-h": usage()
        else: assert False, "unhandled option"

    if m is None or n is None or outdir is None: usage()

    outdir = Path(outdir)
    if not outdir.exists(): outdir.mkdir(parents=True)

    A = np.random.rand(m, n)
    Q, R = np.linalg.qr(A)

    mmwrite(f"{str(outdir)}/A.mtx", A)
    mmwrite(f"{str(outdir)}/Q.mtx", Q)
    mmwrite(f"{str(outdir)}/R.mtx", R)

    sys.exit(0)
