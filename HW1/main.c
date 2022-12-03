# include <stdio.h>
# include <stdlib.h>
# include <math.h>

float e = 0.001;

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

// we need to build a new struct for clusters


int main(int argc, char **argv)
{

    printf("2");
    // decleretion of structs: headVector & cord
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols;
    double n;
    char c;

    // init of head cord
    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    // init of head_vec
    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)

    {
        printf("error 1");

        if (c == '\n')
        {

            curr_cord->value = n; // means: vec[i][j] = n
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


    printf("1");
    //this is where we should put out code at just like in python
    //
    //
    //
    //

    //this is where we should delete all out vetcots
    //
    //
    //
    //

    return 0;
}

*
void kmeans(int k, int iter = 200,struct vector *dataPoints) {
    float e = 0.001;
    int convergenceCNT = 0;
    int iterCNT = 0;

    struct vector centroids;
    int[] converganceArray = calloc(k,sizeof(int));



    // init new cluster vector size k & new array of clusters-size, init as all zeros

    struct vector curr = *dataPoints; // this is the head_vec
    while((iterCNT<=iter) || (convergenceCNT<=k) {

        int[] cluster_size_array = calloc(k,sizeof(int));
        // init of new cluster array of vectors

        while (curr->next != NULL) { // iterates over x in datapoints

            int cnt = 0;
            int min_index;
            float min_val = INFINITY;
            struct cord curr_centroid = head_centroids;

            while(curr_centroid->next != NULL){ //this iterates over the centroids

                float d = euclideanDistance(curr, curr_centroid);
                if(min_val < d){
                    min_index = cnt;
                    min_val = d;
                }
                cnt++


            }
            struct vector tmp = cluster[cnt];


            }
            struct vector tmp = curr_cluster->next;
            curr_cluster->next =
        }
    }


}


vector,int updateCentroid(vector clusters, vector centroids, int convergenceCNT){

}

struct vector getCentroids(struct vector *dataPoints, int k) {



    struct vector *centroids_head_vec, *centroids_curr_vec, *centroids_next_vec;
    struct cord *centroids_head_cord, *centroids_curr_cord, *centroids_next_cord;

    centroids_head_cord = malloc(sizeof(struct cord));
    centroids_curr_cord = centroids_head_cord;
    centroids_curr_cord->next = NULL;

    // init of head_vec
    centroids_head_vec = malloc(sizeof(struct vector));
    centroids_curr_vec = centroids_head_vec;
    centroids_curr_vec->next = NULL;



    int i;
    for( i=0; i<k; i++){
        float val = curr_cord->value;
        while(curr_cord->next != NULL){
            curr_cord = curr_cord->next;
            centroids_curr_cord->value = val;
            centroids_curr_cord->next = malloc(sizeof(struct cord));
            centroids_curr_cord = centroids_curr_cord->next;
            centroids_curr_cord->next = NULL;

        }
        centroids_curr_cord->value = val; // means: vec[i][j] = n
        centroids_curr_vec->cords = centroids_head_cord;
        centroids_curr_vec->next = malloc(sizeof(struct vector));
        centroids_curr_vec = centroids_curr_vec->next;
        centroids_curr_vec->next = NULL;
        centroids_head_cord = malloc(sizeof(struct cord));
        centroids_curr_cord = centroids_head_cord;
        centroids_curr_cord->next = NULL;
    };
}





float euclideanDistance(struct cord *x1,struct cord *x2, int n) {
    float d = 0;
    while (x1->next != NULL){
        d = d + (x1->value - x2->value)*(x1->value - x2->value);
        x1 = x1->next;
        x2 = x2->next;
    }
    d = sqrt(d);
    return d;
}

int inputValidation(int k, int iter, int n){ // n = number of dataPoints. we need to check it on main func
    if((k<=1) || (k>=n) || (k%1 != 0 )){
        printf("Invalid number of clusters!");
        return 1;
    }
    if((iter<=1) || (iter >= 1000) || (iter%1 != 0)) {
        printf("Invalid maximum iteration!");
        return 1;
    }
    return 0;
}

void insertFirst(struct vector head, struct cord x){
    struct vector tmp = head->next;
    head->next = malloc(sizeof(struct vector));
    while(x->next != NULL){

    }


}