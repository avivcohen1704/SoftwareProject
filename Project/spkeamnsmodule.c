#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "spkmeans.h"



PyObject* toPy(int n, double input[n+1][n], PyObject* output);
void create_vec(int n, double curr[n], PyObject* row);
void output_print(int num_of_dp,double  output_array[num_of_dp][num_of_dp]);
void output_print_j(int num_of_dp,double output_array[num_of_dp+1][num_of_dp]);

static PyObject* wrap_spk(PyObject *self, PyObject *args)
{
    int i,j;
    int num_of_dp, size_of_vec;
    PyObject *dp_arr_py;
    PyObject *item1, *item2;
    PyObject *Py_matrix;
    double val;

    if(!PyArg_ParseTuple(args, "iiO", &num_of_dp, &size_of_vec,&dp_arr_py)) {
        return NULL; 
    }

    double cords[size_of_vec];
    double dp_arr[num_of_dp][size_of_vec];
    double wam_array[num_of_dp][num_of_dp];
    double ddg_array[num_of_dp][num_of_dp];
    double gl_array[num_of_dp][num_of_dp];
    double output_array[num_of_dp+1][num_of_dp];

    for(i=0; i<num_of_dp; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<size_of_vec; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++){
            dp_arr[i][j] = cords[j];
        }

    }
    wam_c(num_of_dp,size_of_vec,dp_arr,wam_array);
    ddg_c(num_of_dp, wam_array, ddg_array);
    gl_c(num_of_dp,ddg_array,wam_array,gl_array);
    jacobi_c(num_of_dp, gl_array, output_array);

    return toPy(num_of_dp, output_array, Py_matrix);
     
}  

static void wrap_wam(PyObject *self, PyObject *args)
{
    int i,j;
    int num_of_dp, size_of_vec;
    PyObject *dp_arr_py;
    PyObject *item1, *item2;
    double val;

    if(!PyArg_ParseTuple(args, "iiO", &num_of_dp, &size_of_vec,&dp_arr_py)) {
        return ; 
    }

    double cords[size_of_vec];
    double dp_arr[num_of_dp][size_of_vec];
    double output_array[num_of_dp][num_of_dp];
    for(i=0; i<num_of_dp; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<size_of_vec; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++){
            dp_arr[i][j] = cords[j];
        }

    }

    wam_c(num_of_dp,size_of_vec,dp_arr,output_array);
    output_print(num_of_dp, output_array);
}

static void wrap_ddg(PyObject *self, PyObject *args)
{
    int i,j;
    int num_of_dp, size_of_vec;
    PyObject *dp_arr_py;
    PyObject *item1, *item2;
    double val;

    if(!PyArg_ParseTuple(args, "iiO", &num_of_dp, &size_of_vec,&dp_arr_py)) {
        return;
    }

    double cords[size_of_vec];
    double dp_arr[num_of_dp][size_of_vec];
    double wam_array[num_of_dp][num_of_dp];
    double output_array[num_of_dp][num_of_dp];

    for(i=0; i<num_of_dp; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<size_of_vec; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++){
            dp_arr[i][j] = cords[j];
        }

    }
    wam_c(num_of_dp,size_of_vec,dp_arr,wam_array);
    ddg_c(num_of_dp, wam_array, output_array);
    output_print(num_of_dp, output_array);
}

static void wrap_gl(PyObject *self, PyObject *args)
{
    int i,j;
    int num_of_dp, size_of_vec;
    PyObject *dp_arr_py;
    PyObject *item1, *item2;
    double val;

    if(!PyArg_ParseTuple(args, "iiO", &num_of_dp, &size_of_vec,&dp_arr_py)) {
        return ; 
    }

    double cords[size_of_vec];
    double dp_arr[num_of_dp][size_of_vec];
    double wam_array[num_of_dp][num_of_dp];
    double ddg_array[num_of_dp][num_of_dp];
    double output_array[num_of_dp][num_of_dp];

    for(i=0; i<num_of_dp; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<size_of_vec; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++){
            dp_arr[i][j] = cords[j];
        }

    }
    wam_c(num_of_dp,size_of_vec,dp_arr,wam_array);
    ddg_c(num_of_dp, wam_array, ddg_array);
    gl_c(num_of_dp,ddg_array,wam_array,output_array);
    output_print(num_of_dp, output_array);
}

static void wrap_jacobi(PyObject *self, PyObject *args){
    
    int n,i,j;
    PyObject *dp_arr_py;
    PyObject *item1, *item2;
    double val;

    if(!PyArg_ParseTuple(args, "iO", &n ,&dp_arr_py)) {
        return ; 
    }
    double row[n];
    double matrix[n][n];
    double output_array [n][n];

    for(i=0; i<n; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<n; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            row[j] = val;
        }
        for(j=0; j<n; j++){
            matrix[i][j] = row[j];
        }
    }

    jacobi_c(n, matrix, output_array);
    output_print_j(n, output_array);
}

static PyObject* fit(PyObject *self, PyObject *args){
    int k;
    int iter;
    double e;
    PyObject *dp_arr_py;
    int num_of_dp;
    int size_of_vec;
    PyObject *centroids_arr_py;
    PyObject *item1, *item2;
    double val;
    int i, j;
    

    if(!PyArg_ParseTuple(args, "iidOOii", &k, &iter, &e, &dp_arr_py, &centroids_arr_py, &size_of_vec, &num_of_dp)) {
        return NULL; 
    }

    double dp_arr[num_of_dp][size_of_vec];
    double centroids_arr[k][size_of_vec];
    double cords[size_of_vec];
    
    for(i=0; i<num_of_dp; i++){
        item1 = PyList_GetItem(dp_arr_py,i);
        for(j=0; j<size_of_vec; j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++){
            dp_arr[i][j] = cords[j];
        }

    }

    for(i=0; i<k; i++){
        item1 = PyList_GetItem(centroids_arr_py,i);
        for(j=0; j<size_of_vec;j++){
            item2 = PyList_GetItem(item1, j);
            val = PyFloat_AsDouble(item2);
            cords[j] = val;
        }
        for(j=0; j<size_of_vec; j++) {
            centroids_arr[i][j] = cords[j];
        }
    }



    return kmeans_c( k, size_of_vec, num_of_dp, iter, e, dp_arr, centroids_arr); 

}

static PyMethodDef spkmeansMethods[] = {
{"wrap_spk",
(PyCFunction) wrap_spk,
METH_VARARGS,
PyDoc_STR("calcs the spkmeans algo from given data points")
},

{"wrap_wam",
(PyCFunction) wrap_wam,
METH_VARARGS,
PyDoc_STR("calculates the wheighted adjecency matrix for given data points using the exp squared euclidean distance")},

{"wrap_ddg",
(PyCFunction) wrap_ddg,
METH_VARARGS,
PyDoc_STR("calcs the diagoinal degree matrix of the WAM of given data points")},

{"wrap_gl",
(PyCFunction) wrap_gl,
METH_VARARGS,
PyDoc_STR("calcs the Graph Laplacian for given data points")},

{"wrap_jacobi",
(PyCFunction) wrap_jacobi,
METH_VARARGS,
PyDoc_STR("calc the eigenvalue and eigenvectors of a given matrix")},

{"fit",
(PyCFunction) fit,
METH_VARARGS,
PyDoc_STR("runs the kmean algo from given data points, and centroids")
},

{NULL, NULL , 0, NULL}
};

static struct PyModuleDef spkmeansmodule = {
    PyModuleDef_HEAD_INIT,
    "myspkmeans",
    NULL,
    -1,
    spkmeansMethods
};

PyMODINIT_FUNC PyInit_myspkmeans(void){
    PyObject *m;
    m = PyModule_Create(&spkmeansmodule);
    if (!m) {
        return NULL;
    }
    return m;
}

PyObject* toPy(int n, double input[n+1][n], PyObject* output){
    int i;
    PyObject* row;
    row = PyList_New(n);
    for(i=0; i<n+1; i++){
        create_vec(n, input[i], row);
        PyList_SetItem(output, i, row);
    }
    return output;
}

void create_vec(int n, double curr[n], PyObject* row){
    int i;
    PyObject* py_double;
    for(i=0; i<n; i++){
        py_double = Py_BuildValue("d", curr[i]);
        PyList_SetItem(row, i, py_double);
    }
}

void output_print(int num_of_dp,double output_array[num_of_dp][num_of_dp]){
    
}
void output_print_j(int num_of_dp,double output_array[num_of_dp+1][num_of_dp]){
}
