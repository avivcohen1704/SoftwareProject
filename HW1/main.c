# include <stdio.h>
# include <stdlib.h>
# include <math.h>

float e = 0.001;

//decleration of the funcs
int inputValidation(int k, int iter, int num_of_dp);
struct vector *getCentroids(struct vector *dp_head, int k);
struct cord* createVector(struct cord *x);

//decleration of the structs
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
struct cluster
{
    struct cluster *next_cluster;
    struct vector *next_vector;
};

int main(int argc, char **argv)
{
    struct vector *dp_head, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols;
    double n;
    char c;

    int k;
    int iter;
    int num_of_dp;

    k = atoi(argv[1]);
    iter = atoi(argv[2]);




    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    dp_head = malloc(sizeof(struct vector));
    curr_vec = dp_head;
    curr_vec->next = NULL;

    num_of_dp = 0;

    while (scanf("%lf%c", &n, &c) == 2)
    {
        if (c == '\n')
        {
            num_of_dp++;
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }
        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;

    }

    if (inputValidation(k, iter, num_of_dp)){
        return 0;
    }

    struct vector *centroids_head_vec;
    centroids_head_vec = malloc(sizeof(struct vector));
    centroids_head_vec = getCentroids(dp_head, k); //creates the k centroids

    return 0;
}


int inputValidation(int k, int iter, int num_of_dp){
    if((k<=1) || (k>=num_of_dp) || (k%1 !=0)){
        printf("Invalid number of clusters!");
        return 1;
    }
    if((iter <= 1) || (iter >= 1000) || (iter % 1 != 0)) {
        printf("Invalid maximum iteration!");
        return 1;
    }
    return 0;
}

float euclideanDistance(struct cord *x1, struct cord *x2){
    float d = 0;
    while (x1->next != NULL){
        d = d + (x1->value - x2->value)*(x1->value - x2->value);
        x1 = x1->next;
        x2 = x2->next;
    }
    d = sqrt(d);
    return d;
}

struct vector *getCentroids(struct vector *dp_head, int k){

    //decleration & init of centroids struct
    struct vector *centroids_head_vec, *centroids_curr_vec, *centroids_next_vec;
    struct cord *centroids_head_cord, *centroids_curr_cord, *centroids_next_cord;

    centroids_head_cord = malloc(sizeof(struct cord));
    centroids_curr_cord = centroids_head_cord;
    centroids_curr_cord->next = NULL;

    centroids_head_vec = malloc(sizeof(struct vector));
    centroids_curr_vec = centroids_head_vec;
    centroids_curr_vec->next = NULL;

    struct vector *curr_vec = dp_head;
    struct cord *curr_cord = curr_vec->cords;



    int i;
    for(i=0; i<k; i++){
        centroids_curr_vec->cords = malloc(sizeof(struct cord));
        centroids_curr_vec->cords = createVector(curr_vec->cords);
        centroids_curr_vec->next = malloc(sizeof(struct vector));
        centroids_curr_vec = centroids_curr_vec->next;
        curr_vec=curr_vec->next;
    };
    return centroids_head_vec;
}

//creates a new vector.cords made of the coordinates of a given vector.cords
struct cord* createVector(struct cord *x){
    struct cord *res;
    res = malloc(sizeof(struct cord));
    struct cord *curr;
    curr = res;
    while(x->next != NULL){
        curr->value = x->value;
        curr->next = malloc(sizeof(struct cord));
        curr = curr->next;
        x = x->next;
    }
    curr->value = x->value;
    return res;
}
