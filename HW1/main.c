# include <stdio.h>
# include <stdlib.h>
# include <math.h>

float e = 0.001;
int inputValidation(int k, int iter, int num_of_dp);
struct vector *getCentroids(struct vector *dp_head, int k);
struct cord* createVector(struct cord *x);
void kmeans(struct vector *dp_head, struct vector centroids_head_vec,int k, int iter, int num_of_dp);
struct vector* createEmptyCentroids(int k, int size_of_vector);

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

int main(int argc, char **argv)
{
    struct vector *dp_head, *curr_vec;
    struct cord *head_cord, *curr_cord;
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
    centroids_head_vec = getCentroids(dp_head, k);

    // calls kmean over here;
    

    return 0;
}

void kmeans(struct vector *dp_head, struct vector old_centroids_head_vec,int k, int iter, int num_of_dp){

    int convergence_array[num_of_dp]; // the array of the convergence
    memset(convergence_array,0,num_of_dp);

    int num_of_dp_in_cluster[k];  // the array of the division
    memset(num_of_dp_in_cluster,0,k);

    int convergenceCNT = 0; // for first while loop
    int iterCNT = 0;

    // points to data-point struct
    struct vector *head_vec1, *curr_vec1; 
    struct cord *head_cord1, *curr_cord1;

    // points to old-centroids struct
    struct vector *head_vec2, *curr_vec2;
    struct cord *head_cord2, *curr_cord2;

    head_vec2 = old_centroids_head_vec;
    curr_vec2 = head_vec2;
    curr_cord2 = head_vec2->cords;

    // the new centorids struct
    struct vector *new_head_vec, *new_curr_vec;
    struct cord *new_head_cord, *new_curr_cord, *min_cord; // min_cord - indicates the cord in new centroid 

    while(convergenceCNT<k && iterCNT<iter){
        memset(num_of_dp_in_cluster,0,k); // resets the nuber if dp in cluster

        head_vec1 = dp_head;
        curr_vec1 = head_vec1;
        curr_cord1 = head_vec1->cords;

        new_head_vec = createEmptyCentroids(k/*,size of cord*/);
        new_curr_vec = new_head_vec;
        new_curr_cord = new_head_vec->cords;

        while(curr_vec1 != NULL){ // iterates over Data Points
            int i=0; // to where in new centroids we insert
            int j=0; // 

            float distance;
            float min_distance = -1;

            min_cord = new_head_cord;

            while(curr_vec2 != NULL){ // iterate over centroids
                distance = euclideanDistance(curr_cord1, curr_cord2);
                if((min_distance ==-1) || (distance < min_distance)){
                    min_cord = new_curr_cord;
                    j = i;
                }

                j++;
                curr_vec2 = curr_vec2->next;

            }
            num_of_dp_in_cluster[j] += 1;
            min_cord = addCords(curr_cord1, min_cord);

            curr_vec1 = curr_vec1->next;
            
        }
        new_head_vec = divideCentroid(new_head_vec, num_of_dp_in_cluster);
        convergence_array = check_converge(new_head_vec, head_vec1, convergence_array);

    }




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

struct vector* createEmptyCentroids(int k, int size_of_vector){
    struct vector *vec, *curr_vec;
    struct cord *cord, *curr_cord;

    cord = malloc(sizeof(struct cord));
    curr_cord = cord;
    curr_cord->next = NULL;

    vec = malloc(sizeof(struct vector));
    curr_vec = vec;
    curr_vec->next = NULL;

    for(int i =0; i<k; i++){
        for(int j=0; j<size_of_vector; j++){
            curr_cord->value = 0;
            curr_cord->next = malloc(sizeof(struct cord));
            curr_cord = curr_cord->next;
            curr_cord->next = NULL;
        }
        curr_vec->next = malloc(sizeof(struct vector));
        curr_vec = curr_vec->next;
        curr_vec->cords = malloc(sizeof(struct cord));
        curr_cord = curr_vec->cords;
    }
    return vec;


}

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
