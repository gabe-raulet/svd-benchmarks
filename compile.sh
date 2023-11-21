#!/bin/bash
#clang -llapacke test.c kiss.c mmio.c mmio_dense.c linalg_routines.c
clang -llapacke test_qr.c kiss.c mmio.c mmio_dense.c linalg_routines.c
