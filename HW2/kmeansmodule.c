#define PY_SSIZE_T_CLEAN
#include <Python.h>

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>



struct cord* createVector(struct cord *x);
struct vector* createEmptyCentroids(int k, int size_of_vector);
double euclideanDistance(struct cord *x1, struct cord *x2);
int getCordLength(struct vector *dp_head);
void divide_centroid(struct vector *new_centroid, int num_of_dp_in_cluster[], int k);
void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k, double e);
void addCords(struct cord *curr_cord1, struct cord *min_cord);
void create_Array(int array[], int len);
struct cord* createEmptyCord(int size_of_vector);
struct vector* copyOf(struct vector *old_centroid);
void freeSpaceCord(struct cord *Cord);
void freeSpaceVec(struct vector *vec);
int isNum (char *s);
int isDigit(char c);
struct cords* create_cord_from_arr(int size_of_vec, double cord[size_of_vec]);
struct vector* arr_to_ll(int num_points, int size_of_vec, double point_arr[num_points][size_of_vec],int bool);
int kmeans_c(int k, int size_of_vec , int num_of_dp,int iter, double e, double dp_arr[num_of_dp][size_of_vec], double *centroids_arr[k][size_of_vec]);
PyObject* kmeans(struct vector *dp_head, struct vector *old_centroids_head_vec,int k, int iter, int num_of_dp,double e, int size_of_vec);
PyObject* ll_to_arr(struct vector *centroids, int k, int size_of_vec);
PyObject* create_vec_from_arr(struct cord *cord,  int size_of_vec);


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


int kmeans_c(int k, int size_of_vec , int num_of_dp,int iter, double e, double dp_arr[num_of_dp][size_of_vec], double *centroids_arr[k][size_of_vec])
{
    struct vector *dp_head;
    struct vector *centroids_head_vec;

    dp_head = arr_to_ll(num_of_dp, size_of_vec, dp_arr, 0);
    centroids_head_vec = arr_to_ll(k, size_of_vec, centroids_arr, 1);

    return kmeans(dp_head, centroids_head_vec, k, iter, num_of_dp, e, size_of_vec);
    }

PyObject* kmeans(struct vector *dp_head, struct vector *old_centroids_head_vec,int k, int iter, int num_of_dp,double e, int size_of_vec){

    int cord_length;

    int *convergence_array; /* the array of the convergence*/

    int *num_of_dp_in_cluster; /* the array of the division*/

    int convergenceCNT;/* = 0; // for first while loop*/
    int iterCNT;/* = 0;*/


    struct vector *head_vec1, *curr_vec1; /* points to data-point struct*/
    struct cord  *curr_cord1;/**head_cord1,*/


    struct vector *head_vec2, *curr_vec2; /* points to old-centroids struct*/
    struct cord *curr_cord2;/**head_cord2,*/


    struct vector *new_head_vec, *new_curr_vec; /* the new centorids struct*/
    struct cord *new_curr_cord, *min_cord; /* *new_head_cord uninitiallized,  min_cord - indicates the cord in new centroid*/

    PyObject* final_centroids_py;

    cord_length = getCordLength(dp_head);
    convergence_array = calloc(num_of_dp , (sizeof(int)));
    create_Array(convergence_array, num_of_dp);
    num_of_dp_in_cluster = calloc(k , (sizeof(int)));
    create_Array(num_of_dp_in_cluster, k);
    convergenceCNT = 0;
    iterCNT = 0;
    head_vec2 = old_centroids_head_vec;
    curr_vec2 = head_vec2;
    curr_cord2 = head_vec2->cords;

    while(convergenceCNT<k && iterCNT<iter){
        int cnt;
        int l;
        create_Array(num_of_dp_in_cluster, k); /* resets the nuber if dp in cluster*/

        head_vec1 = dp_head;
        curr_vec1 = head_vec1;
        curr_cord1 = head_vec1->cords;
        if(iterCNT!=0){
            freeSpaceVec(new_head_vec);
        }

        new_head_vec = createEmptyCentroids(k, cord_length);

        while(curr_vec1->cords != NULL){ /* iterates over Data Points*/
            int i;/*=0; // to where in new centroids we insert*/
            int j;
            double distance;
            double min_distance;

            new_curr_vec = new_head_vec;
            new_curr_cord = new_head_vec->cords;
            curr_vec2 = head_vec2;
            curr_cord2 = curr_vec2->cords;

            i=0;
            j=0;
            min_distance = -1;
            /*min_cord = new_head_cord;*/

            while(curr_vec2 != NULL){ /* iterate over old centroids*/
                distance = euclideanDistance(curr_cord1, curr_cord2);
                if((min_distance ==-1) || (distance < min_distance)){
                    min_cord = new_curr_cord;
                    j = i;
                    min_distance = distance;
                }

                i++;
                if((curr_vec2->next == NULL)){
                    break;
                }
                curr_vec2 = curr_vec2->next;
                curr_cord2 = curr_vec2->cords;
                if(new_curr_vec->next != NULL){
                    new_curr_vec = new_curr_vec->next;
                    new_curr_cord = new_curr_vec->cords;}

            }
            num_of_dp_in_cluster[j] += 1;
            addCords(curr_cord1,min_cord);
            if(curr_vec1->next!= NULL){
                if(curr_vec1->next->cords == NULL){
                    break;
                }
            }
            curr_vec1 = curr_vec1->next;
            curr_cord1 = curr_vec1->cords;

        }
        divide_centroid(new_head_vec, num_of_dp_in_cluster, k);
        check_converge(new_head_vec, head_vec1, convergence_array, k, e);
        cnt = 0;
        for (l=0; l<k; l++){
            if(convergence_array[l]==1){
                cnt+=1;
            }
        }
        convergenceCNT = cnt;
        iterCNT +=1;

        freeSpaceVec(head_vec2);
        curr_vec2 = copyOf(new_head_vec);
        head_vec2 = curr_vec2;



    }

    final_centroids_py = ll_to_arr(new_head_vec, k, size_of_vec);

    freeSpaceVec(head_vec2);
    freeSpaceVec(dp_head);
    freeSpaceVec(new_head_vec);
    free(convergence_array);
    free(num_of_dp_in_cluster);

    return final_centroids_py;

}

double euclideanDistance(struct cord *x1, struct cord *x2){

    double d = 0;
    while (x1 != NULL){
        d = d + (x1->value - x2->value)*(x1->value - x2->value);

        if(x1->next ==NULL){
            break;
        }
        x1 = x1->next;
        x2 = x2->next;
    }
    d = pow(d,0.5);
    return d;
}


struct vector* createEmptyCentroids(int k, int size_of_vector){
    struct vector *vec, *curr_vec;
    int i;
    vec = calloc(1,sizeof(struct vector));
    curr_vec = vec;
    vec->next = NULL;

    for(i = 0; i<k; i++){
        curr_vec->cords = createEmptyCord(size_of_vector);
        if(i != (k-1)){
            curr_vec->next = calloc(1,sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
        }
    }
    return vec;
}

struct cord* createVector(struct cord *x){
    struct cord *res;
    struct cord *curr1, *curr2;
    res = calloc(1,sizeof(struct cord));
    curr1 = res;
    curr2 = x;
    while(curr2->next != NULL){
        curr1->value = curr2->value;
        curr1->next = calloc(1,sizeof(struct cord));
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    curr1->value = curr2->value;
    curr1->next = NULL;
    return res;
}

int getCordLength(struct vector *dp_head){
    int res = 0;
    struct cord *curr_cord;
    curr_cord = dp_head->cords;
    while(curr_cord != NULL){
        res++;
        curr_cord = curr_cord->next;
    }
    return res;
}

void divide_centroid(struct vector *new_centroid, int num_of_dp_in_cluster[], int k){
    struct vector *curr_vec;
    struct cord *curr_cord;
    int i;
    curr_vec = new_centroid;
    curr_cord = new_centroid->cords;
    for(i=0;i<k; i++){
        while(curr_cord != NULL){
            curr_cord->value = (curr_cord->value)/(num_of_dp_in_cluster[i]);
            curr_cord = curr_cord->next;
        }

        if(curr_vec->next == NULL){
            break;
        }
        curr_vec = curr_vec->next;
        curr_cord = curr_vec->cords;
    }
}

void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k, double e){
    int i;
    for(i=0; i<k; i++){
        if(convergence_array[i]==1){
            continue;
        }
        if(euclideanDistance(new_head_vec->cords,head_vec1->cords) < e){
            convergence_array[i] = 1;
        }
    }
}

void addCords(struct cord *curr_cord1, struct cord *min_cord){
    struct cord *curr_min_cord, *curr_cord;
    curr_cord = curr_cord1;
    curr_min_cord = min_cord;
    while(curr_cord != NULL){
        curr_min_cord->value += curr_cord->value;
        if((curr_cord->next == NULL) || (curr_min_cord->next == NULL)){
            break;
        }
        curr_cord = curr_cord->next;
        curr_min_cord = curr_min_cord->next;
    }
}

void create_Array(int array[], int len){
    int i;
    for( i=0; i<len; i++){
        array[i] = 0;
    }
}

struct cord* createEmptyCord(int size_of_vector){
    struct cord *head_cord, *curr_cord;
    int i;
    head_cord = calloc(1,sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;
    for(i=1;i<size_of_vector; i++){
        curr_cord->value = 0;
        if(i!=size_of_vector){
        curr_cord->next = calloc(1,sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
        }
    }
    return head_cord;
}

struct vector* copyOf(struct vector *old_centroid){
    struct vector *new_centroids_head, *curr_vec1, *curr_vec2;

    new_centroids_head = calloc(1,sizeof(struct vector));
    new_centroids_head->next = NULL;
    new_centroids_head->cords = NULL;
    curr_vec1 = new_centroids_head;
    curr_vec2 = old_centroid;

    while(curr_vec2 != NULL){
        curr_vec1->cords = createVector(curr_vec2->cords);
        if(curr_vec2->next != NULL){
            curr_vec1->next = calloc(1,sizeof(struct vector));
            curr_vec1 = curr_vec1->next;
            curr_vec1->next = NULL;
        }
        if(curr_vec2->next == NULL){
            break;
        }
        curr_vec2 = curr_vec2->next;
    }
    return new_centroids_head;
}

void freeSpaceVec(struct vector *vec){
    struct vector *curr, *tmp;
    curr = vec;
    while (curr != NULL)
    {
        freeSpaceCord(curr->cords);
        curr = curr->next;
    }
    curr = vec;
    tmp = vec;
    while (curr != NULL){
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

void freeSpaceCord(struct cord *cord){
    struct cord *curr, *tmp;
    curr = cord;
    while(curr != NULL){
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
}

int isNum (char *s){
    int n;
    int i;
    n = strlen(s);
    for(i=0;i<n;i++){
        if(!isDigit(s[i])){
            return 0;
        }
    }
    return 1;
}

int isDigit(char c){
    if(c>='0' && c<='9'){
        return 1;
    }
    return 0;
}

PyObject* ll_to_arr(struct vector *centroids, int k, int size_of_vec){
    int i;
    struct vector *curr_vec;
    PyObject* res = PyList_New(k);
    PyObject* cord = PyList_New(size_of_vec);
    curr_vec = centroids;
    for(i=0; i<k; i++){
        cord = create_vec_from_arr(curr_vec->cords, size_of_vec);
        PyList_SetItem(res, i, cord);
        if(i == k-1){
            break;
        }
        curr_vec = curr_vec->next;
    }
    return res;
}

PyObject* create_vec_from_arr(struct cord *cord,  int size_of_vec){
    struct cord* curr_cord;
    int i,r;
    PyObject* python_double;
    PyObject* res = PyList_New(size_of_vec);
    curr_cord = cord;
    for(i=0; i<size_of_vec; i++){
        python_double = Py_BuildValue("d",curr_cord->value);
        PyList_SetItem(res, i, python_double);
        if(i == size_of_vec-1){
            break;
        }
        curr_cord = curr_cord->next;
    }
    return res;
}

struct vector* arr_to_ll(int num_points, int size_of_vec, double point_arr[num_points][size_of_vec],int bool){
    struct vector *head_vec, *curr_vec;
    head_vec = calloc(1,sizeof(struct vector));
    curr_vec = head_vec;
    int i;
    for(i=0; i<num_points; i++){
        curr_vec->cords = create_cord_from_arr(size_of_vec, point_arr[i]);
        if((bool) && (i == num_points-1)){
            break;
        }
        curr_vec->next = calloc(1,sizeof(struct vector));;
        curr_vec = curr_vec->next;
    }
    return head_vec;
}

struct cords* create_cord_from_arr(int size_of_vec, double cord[size_of_vec]){
    struct cord *head_cord, *curr_cord;
    head_cord = calloc(1,sizeof(struct cord));
    curr_cord = head_cord;
    int i;
    for(i=0; i<size_of_vec; i++){
        curr_cord->value = cord[i];
        if(i == size_of_vec-1){
            break;
        }
        curr_cord->next = calloc(1,sizeof(struct cord));
        curr_cord = curr_cord->next;
    }
    return head_cord;
}


static PyObject* kmeans_wrap(PyObject *self, PyObject *args)
{
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
    

    /* This parses the Python arguments into a double (d)  variable named z and int (i) variable named n*/
    if(!PyArg_ParseTuple(args, "iidOOii", &k, &iter, &e, &dp_arr_py, &centroids_arr_py, &size_of_vec, &num_of_dp)) {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
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



/* This builds the answer ("d" = Convert a C double to a Python floating point number) back into a python object */
    return kmeans_c( k, size_of_vec, num_of_dp, iter, e, dp_arr, centroids_arr); /*  Py_BuildValue(...) returns a PyObject*  */
}

static PyMethodDef kmeansMethods[] = {
    {"kmeans_wrap",                   /* the Python method name that will be used */
      (PyCFunction) kmeans_wrap, /* the C-function that implements the Python function and returns static PyObject*  */
      METH_VARARGS,           /* flags indicating parameters
accepted for this function */
      PyDoc_STR("Calcs the kmeans algorithm for the given centroids")}, /*  The docstring for the function */
    {NULL, NULL, 0, NULL}     /* The last entry must be all NULL as shown to act as a
                                 sentinel. Python looks for this entry to know that all
                                 of the functions for the module have been defined. */
};

static struct PyModuleDef kmeansmodule = {
    PyModuleDef_HEAD_INIT,
    "kmeans_capi", /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,  /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    kmeansMethods /* the PyMethodDef array from before containing the methods of the extension */
};

PyMODINIT_FUNC PyInit_kmeans_capi(void)
{
    PyObject *m;
    m = PyModule_Create(&kmeansmodule);
    if (!m) {
        return NULL;
    }
    return m;
}
