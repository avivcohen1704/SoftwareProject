#include <Python.h>
#include "spkeamns.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>


int ** wam_c(int n, int[n][n] arr);
double exp_euclidean_distance(int n double[n] x, double[n] y);

int ** wam_c(int n, int [n][n] arr){
    int i,j;
    double ret [n][n];
    for (i=0; i<n; i++){
        for(j=0;j<n;j++){
            if(i==j){
                ret[i][j]=0;
            }
            else{
                ret[i][j]= exp_euclidean_distance(arr[i],arr[j]);
            }
        }
    }
    return ret;
}


double exp_euclidean_distance(int n double[n] x, double[n] y){
    double res;
    int i;
    double sum;
    sum=0;
    for (i=0;i<n;i++){
        sum = sum + pow((x[i]-y[i]),2);
    }
    res = exp((-sum)/2);
    return res;
}
