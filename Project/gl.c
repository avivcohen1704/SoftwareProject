#include <Python.h>
#include "spkeamns.h"

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

double ** gl_c(int n, double[n][n] D, double[n][n]W);

double ** gl_c(int n, double[n][n] D, double[n][n]W){
    int i,j;
    double [n][n] L;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            L[i][j]= D[i][j] - W[i][j];
        }
    }
    return L;
}
