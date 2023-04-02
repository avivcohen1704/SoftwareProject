# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
#include "spkmeans.h"



double exp_euclidean_distance(int n, double x[n] , double y[n] );

void wam_c(int n, int m, double arr[n][m] , double output_array[n][n]){
    int i,j;
    
    for (i=0; i<n; i++){
        for(j=0;j<n;j++){
            if(i==j){
                output_array[i][j]=0;
            }
            else{
                output_array[i][j]= exp_euclidean_distance(m, arr[i],arr[j]);
            }
            
        }
    }
    
    
}


double exp_euclidean_distance(int n, double x[n] , double y[n] ){
    double res;
    int i;
    double sum;
    sum=0;
    res = 0;
    for (i=0;i<n;i++){

        sum = sum + pow((x[i]-y[i]),2);
    }
    

    res = exp((-sum)/2);
    return res;
}
