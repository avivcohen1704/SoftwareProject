# ifndef SPKMEANS_H_
# define SPKMEANS_H_
#include <Python.h>

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


void wam_c(int n, int m, double arr[n][m] , double output_array[n][n]);

void ddg_c(int n, double W[n][n], double D[n][n]);

void gl_c(int n, double D[n][n], double W[n][n], double output_array[n][n]);

void jacobi_c(int n, double A[n][n], double output_array[n+1][n]);

PyObject* kmeans_c(int k, int size_of_vec , int num_of_dp,int iter, double e, double dp_arr[num_of_dp][size_of_vec], double centroids_arr[k][size_of_vec]);

# endif
