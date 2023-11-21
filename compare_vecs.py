#!/usr/bin/env python

import sys
import numpy as np

def usage():
    sys.stderr.write("Usage: {} <vec1> <vec2>\n".format(sys.argv[0]))
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        usage()

    vec1 = np.loadtxt(sys.argv[1])
    vec2 = np.loadtxt(sys.argv[2])

    m = min(len(vec1), len(vec2))
    vec1 = vec1[:m]
    vec2 = vec2[:m]

    sys.stdout.write("norm = {}\n".format(np.linalg.norm(vec1 - vec2)))
    sys.stdout.flush()

