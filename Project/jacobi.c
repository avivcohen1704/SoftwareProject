#include <Python.h>
#include "spkeamns.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

double eps = 0.000001;
int max_iter=100;

double ** jacobi_c(int n, double[n][n] A);
int * max_off_diag(int n, double[n][n] A);
int sign(double a);
double ** rotation(int n,double s,c, double [2] pivot, double[n][n] A);
double** ID(int n);
double ** dot(int n, double[n][n] a, double[n][n] b);
double sum_dot(int n, double [n]row, double[n]col);
double * calc_col(int j, int n, double [n][n] matrix);
int check_converge(int n, double [n][n] A, double [n][n] new_A);
double ** add_eigenV(int n, double [n][n] A, double [n][n] V);




double ** jacobi_c(int n, double[n][n] A){
    int iter,i,j;
    double [n+1][n] res;
    double [n][n] V,P,new_A;
    V = ID(n);

    for(iter=0;iter<max_iter;iter++){
        double theta, t, c, s;
        int[2] pivot;
        P = ID(n);
        pivot = max_off_diag(n,A);
        theta = (A[pivot[1]][pivot[1]]-A[pivot[0]][pivot[0]])/(2*A[pivot[0]][pivot[1]]);
        t = (sign(theta))/(abs(theta)+pow(pow(theta,2)+1,0.5));
        c = 1/ pow(pow(t,2)+1,0.5);
        s = t*c;
        new_A = rotation(n , s, c ,pivot, A);
        P[pivot[0]][pivot[0]] = c;
        P[pivot[1]][pivot[1]] = c;
        P[pivot[1]][pivot[0]] = -s;
        P[pivot[0]][pivot[1]] = s;
        V = dot(n,V,P);

        if (check_converge(n,A,new_A)){break;}
        A = new_A;
    }
    res = add_eigenV(n,new_A,V);
    return res;

}


int * max_off_diag(int n, double[n][n] A){
    int [2] ret;
    int i,j;
    double max;
    max = -1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                continue;
            }
            if(abs(A[i][j])>max){
                ret[0] = i;
                ret[1] = j;
            }
        }
    }
    return ret;
}

int sign(double a){
    if(a<0){
        return -1;
    }
    else{
        return 1;
    }
}

double ** rotation(int n,double s,c, double [2] pivot, double[n][n] A){
    int r,i,j,k,l;
    double [n][n] new_A;
    i = pivot[0];
    j = pivot[1];
    for (k=0;k<n;k++){
        for (l=0;l<n;l++){
            new_A[k][l] = A[k][l];
        }
    }

    for(r=0; i<n; i++){                        /*#1 & #2*/
        if (r != i || r != j){
            new_A[r][i] = c*A[r][i] - s*A[r][j];
            new_A[r][j] = c*A[r][j] + s*A[r][i];
        }
    }
    new_A[i][i] = pow(c,2)*A[i][i] + pow(s,2)*A[j][j]-2*s*c*A[i][j];   /*#3*/
    new_A[j][j] = pow(s,2)*A[i][i] + pow(c,2)*A[j][j] + 2*c*s*A[i][j]; /*#4*/ 
    new_A[i][j] = 0;                                                   /*#5*/
    
    return new_A;
}

double** ID(int n){
    double [n][n] res;
    int i,j;
    for (i=0; i<n;i++){
        for(j=0;j<n;j++){
            if (i == j){
                res[i][j] = 1;
            }
            else{res[i][j] = 0;}
        }
    }
    return res;
}

double ** dot(int n, double[n][n] a, double[n][n] b){
    int i,j;
    double [n][n] ret;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            col = calc_col(j,n,b);
            ret[i][j] = sum_dot(n,a[i],col);
        }
    }
    return ret;

}

double sum_dot(int n, double [n]row, double[n]col){
    double sum;
    int i;
    sum =0;
    for(i=0;i<n;i++){
        sum = sum + row[i]*col[i];
    }
    return sum;
    
}

double * calc_col(int j, int n, double [n][n] matrix){
    double [n] col;
    int i;
    for (i=0; i<n; i++){
        col[i] = matrix[i][j];
    }
    return col;
}

int check_converge(int n, double [n][n] A, double [n][n] new_A){
    int i,j;
    double d1,d2;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            if(i==j){continue;}
            else{
                d1 = d1 + pow(A[i][j],2);
            }
        }
    }
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            if(i==j){continue;}
            else{
                d2 = d2 + pow(new_A[i][j],2);
            }
        }
    }
    if ((d1-d2)<=eps){return 1;}
    return 0;
}

double ** add_eigenV(int n, double [n][n] A, double [n][n] V){
    double [n+1][n] res;
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            res[i][j] = V[i][j];
        }
    }
    for (i=0;i<n;i++){
        res[n+1][i] = A[i][i];
    }
    return res;
}
