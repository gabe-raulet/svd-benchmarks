
/*
 * implement C version of the "create_test.py" script
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>


void usage(const char *prg)
{
    fprintf(stderr, "Usage: %s [options] -m <number of rows> -n <number of columns> -r <rank> -o <matrix file> -S <singular values file>\n", prg);
    fprintf(stderr, "Options: -d FLOAT   the dominant singular value (default: 100.0)\n");
    fprintf(stderr, "         -a FLOAT   the damping factor (default: 2.0)\n");
    fprintf(stderr, "         -U PATH    left singular values matrix\n");
    fprintf(stderr, "         -V PATH    right singular values matrix (transposed)\n");
    fprintf(stderr, "         -h         print this help message\n");
    exit(1);
}

//if __name__ == "__main__":
//    try: opts, args = getopt.getopt(sys.argv[1:], "m:n:r:o:S:d:a:U:V:h", ["dominant-value=", "damping=", "help"])
//    except getopt.GetoptError as err:
//        sys.stderr.write("{}\n".format(err))
//        usage()
//
//    nrows, ncols, rank, mat_file, sval_file, U_file, Vt_file = None, None, None, None, None, None, None
//    dom_sval, damping = 100.0, 2.0
//
//    for o, a in opts:
//        if o == "-m": nrows = int(a)
//        elif o == "-n": ncols = int(a)
//        elif o == "-r": rank = int(a)
//        elif o == "-o": mat_file = a
//        elif o == "-S": sval_file = a
//        elif o == "-U": U_file = a
//        elif o == "-V": Vt_file = a
//        elif o in ("-d", "--dominant-value"): dom_sval = float(a)
//        elif o in ("-a", "--damping"): damping = float(a)
//        elif o in ("-h", "--help"): usage()
//        else: assert False, "unhandled option"
//
//    if nrows is None or ncols is None or rank is None or mat_file is None or sval_file is None:
//        sys.stderr.write("Missing required arguments\n")
//        usage()
//
//  implement int main(argc, char *argv[]) using the above python code as a guide
//

int main(int argc, char *argv[])
{
    int nrows = 0, ncols = 0, rank = 0;
    char *mat_file = NULL, *sval_file = NULL, *U_file = NULL, *Vt_file = NULL;
    double dom_sval = 100., damping = 2.:

    int opt;
    while ((opt = getopt(argc, argv, "m:n:r:o:S:d:a:U:V:h")) >= 0)
    {
        if (opt == 'm') nrows = atoi(optarg);
        else if (opt == 'n') ncols = atoi(optarg);
        else if (opt == 'r') rank = atoi(optarg);
        else if (opt == 'o') mat_file = optarg;
        else if (opt == 'S') sval_file = optarg;
        else if (opt == 'U') U_file = optarg;
        else if (opt == 'V') Vt_file = optarg;
        else if (opt == 'd') dom_sval = atof(optarg);
        else if (opt == 'a') damping = atof(optarg);
        else if (opt == 'h') usage(argv[0]);
        else assert(0);
    }

    if (nrows == 0 || ncols == 0 || rank == 0 || !mat_file || !sval_file)
    {
        fprintf(stderr, "Missing required arguments\n");
        usage(argv[0]);
    }

    assert(rank <= ncols && nrows >= ncols);

    return 0;
}
