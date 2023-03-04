# ifndef SPKMEANS_H_
# define SPKMEANS_H_

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

int ** wam_c(int n, int[n][n] arr);

int ** ddg_c(int n, double[n][n]W);

double ** gl_c(int n, double[n][n] D, double[n][n]W);

double ** jacobi_c(int n, double[n][n] A);


# endif
