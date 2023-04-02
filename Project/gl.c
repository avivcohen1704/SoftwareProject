# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
#include "spkmeans.h"



void gl_c(int n, double D[n][n], double W[n][n], double L[n][n]) {
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            L[i][j]= D[i][j] - W[i][j];
        }
    }
}
