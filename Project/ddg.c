#include <Python.h>
#include "spkeamns.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

int ** ddg_c(int n, double[n][n]W);
double sum_row (int n; double [n] arr);

int ** ddg_c(int n, double[n][n]W){
    int i, j;
    double [n][n] D;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i!=j){
                D[i][j]=0;
            }
            else{
                D[i][j]= sum_row(n, W[i]);
            }
        }
    }
    return D;

}

double sum_row (int n; double [n] arr){
    int i;
    double ret;
    ret=0;
    for (i=0;i<n;i++){
        ret = ret + arr[i];
    }
    return ret;

}
