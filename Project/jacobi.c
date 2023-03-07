#include <Python.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
#include "spkmeans.h"


double eps = 0.000001;
int max_iter=100;

void max_off_diag(int n, double A[n][n], int pivot[2]);
int sign(double a);
void rotation(int n,double s,double c, int pivot [2], double A[n][n], double new_A[n][n]);
void ID(int n, double res[n][n]);
void dot(int n, double a [n][n] , double b[n][n]);
double sum_dot(int n, double row[n], double col[n]);
void calc_col(int j, int n, double matrix[n][n], double col[n] );
int check_converge(int n, double A[n][n] , double new_A[n][n] );
void add_eigenV(int n, double A [n][n] , double V[n][n], double res[n+1][n] );



    void jacobi_c(int n, double A[n][n] , double res[n+1][n]){
    int iter,i,j;
    double V[n][n];
    double P[n][n];
    double new_A[n][n];

    ID(n,V);

    for(iter=0;iter<max_iter;iter++){
        double theta, t, c, s;
        int pivot[2] ;
        ID(n,P);
        max_off_diag(n,A, pivot);
        theta = (A[pivot[1]][pivot[1]]-A[pivot[0]][pivot[0]])/(2*A[pivot[0]][pivot[1]]);
        t = (sign(theta))/(abs(theta)+pow(pow(theta,2)+1,0.5));
        c = 1/ pow(pow(t,2)+1,0.5);
        s = t*c;
        rotation(n , s, c ,pivot, A, new_A);
        P[pivot[0]][pivot[0]] = c;
        P[pivot[1]][pivot[1]] = c;
        P[pivot[1]][pivot[0]] = -s;
        P[pivot[0]][pivot[1]] = s;
        dot(n,V,P);

        if (check_converge(n,A,new_A)){break;}
        A = new_A;
    }
    add_eigenV(n,new_A,V, res);
}


void max_off_diag(int n, double A[n][n], int pivot[2]){
    int i,j;
    double max;
    max = -1;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j){
                continue;
            }
            if(abs(A[i][j])>max){
                pivot[0] = i;
                pivot[1] = j;
            }
        }
    }
}

int sign(double a){
    if(a<0){
        return -1;
    }
    else{
        return 1;
    }
}

void rotation(int n,double s, double c, int pivot [2], double A[n][n] , double new_A[n][n]){
    int r,i,j,k,l;
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
    }

void ID(int n, double res[n][n]){
    int i,j;
    for (i=0; i<n;i++){
        for(j=0;j<n;j++){
            if (i == j){
                res[i][j] = 1;
            }
            else{res[i][j] = 0;}
        }
    }
}

void dot(int n, double a[n][n] , double b[n][n]){
    int i,j;
    double col[n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            calc_col(j,n,b, col);
            a[i][j] = sum_dot(n,a[i],col);
        }
    }
}

double sum_dot(int n, double row[n], double col[n]){
    double sum;
    int i;
    sum =0;
    for(i=0;i<n;i++){
        sum = sum + row[i]*col[i];
    }
    return sum;
    
}

void calc_col(int j, int n, double matrix[n][n],double col[n] ){
    int i;
    for (i=0; i<n; i++){
        col[i] = matrix[i][j];
    }
}

int check_converge(int n, double A[n][n] , double new_A[n][n] ){
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

void add_eigenV(int n, double A[n][n] , double V[n][n], double res[n+1][n]){
    
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            res[i][j] = V[i][j];
        }
    }
    for (i=0;i<n;i++){
        res[n+1][i] = A[i][i];
    }
}
