#!/bin/bash
clang -O2 -o test_svd -llapacke test_svd.c kiss.c mmio.c mmio_dense.c linalg_routines.c
clang -O2 -o test_qr -llapacke test_qr.c kiss.c mmio.c mmio_dense.c linalg_routines.c
