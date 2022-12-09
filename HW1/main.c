# include <stdio.h>
# include <stdlib.h>
# include <math.h>

float e = 0.001;
int inputValidation(int k, int iter, int num_of_dp);
struct vector *getCentroids(struct vector *dp_head, int k);
struct cord* createVector(struct cord *x);
void kmeans(struct vector *dp_head, struct vector *centroids_head_vec,int k, int iter, int num_of_dp);
struct vector* createEmptyCentroids(int k, int size_of_vector);
float euclideanDistance(struct cord *x1, struct cord *x2);
int getCordLength(struct vector *dp_head);
void divide_centroid(struct vector *new_centroid,int num_of_dp_in_cluster[],int k);
void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k);
void addCords(struct cord *curr_cord1, struct cord *min_cord);
void create_Array(int array[], int len);
struct cord* createEmptyCord(int size_of_vector);
struct vector* copyOf(struct vector *old_centroid);



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
    //centroids_head_vec = malloc(sizeof(struct vector)); // is not supposed to be here
    centroids_head_vec = getCentroids(dp_head, k);

    kmeans(dp_head, centroids_head_vec, k, iter, num_of_dp);


    return 0;
}

void kmeans(struct vector *dp_head, struct vector *old_centroids_head_vec,int k, int iter, int num_of_dp){

    int cord_length;
    cord_length = getCordLength(dp_head);

    int convergence_array[num_of_dp];// the array of the convergence
    create_Array(convergence_array, num_of_dp);

    int num_of_dp_in_cluster[k];  // the array of the division
    create_Array(num_of_dp_in_cluster, k);

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
        create_Array(num_of_dp_in_cluster, k); // resets the nuber if dp in cluster

        head_vec1 = dp_head;
        curr_vec1 = head_vec1;
        curr_cord1 = head_vec1->cords;

        new_head_vec = createEmptyCentroids(k, cord_length);

        while(curr_vec1->cords != NULL){ // iterates over Data Points
            new_curr_vec = new_head_vec;
            new_curr_cord = new_head_vec->cords;
            curr_vec2 = head_vec2;
            curr_cord2 = curr_vec2->cords;
            int i=0; // to where in new centroids we insert
            int j=0; //

            float distance;
            float min_distance = -1;

            min_cord = new_head_cord;


            while(curr_vec2 != NULL){ // iterate over old centroids
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

            if(curr_vec1->next->cords == NULL){
                break;
            }
            curr_vec1 = curr_vec1->next;
            curr_cord1 = curr_vec1->cords;

        }
        divide_centroid(new_head_vec, num_of_dp_in_cluster, k);
        check_converge(new_head_vec, head_vec1, convergence_array, k);
        int cnt = 0;
        int l;
        for (l=0; l<k; l++){
            if(convergence_array[l]==1){
                cnt+=1;
            }
        }
        convergenceCNT = cnt;
        iterCNT +=1;
        curr_vec2 = copyOf(new_head_vec);



    }
    new_curr_vec = new_head_vec;
    new_curr_cord = new_curr_vec->cords;

    while(new_curr_vec != NULL){
        while(new_curr_cord->next != NULL){
            printf("%.4f" , new_curr_cord->value);
            printf(",");
            new_curr_cord = new_curr_cord->next;
        }
        printf("%.4f" , new_curr_cord->value);
        printf("\n");
        if(new_curr_vec->next == NULL){
            break;
        }
        new_curr_vec = new_curr_vec->next;
        new_curr_cord = new_curr_vec->cords;
    }
}


int inputValidation(int k, int iter, int num_of_dp){
    if((k<=1) || (k>=num_of_dp) || (k%1 !=0)){
        printf("Invalid number of clusters!");
        return 1;
    }
    if((iter < 1) || (iter >= 1000) || (iter % 1 != 0)) {
        printf("Invalid maximum iteration!");
        return 1;
    }
    return 0;
}

float euclideanDistance(struct cord *x1, struct cord *x2){

    float d = 0;
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

struct vector *getCentroids(struct vector *dp_head, int k){

    //decleration & init of centroids struct
    struct vector *centroids_head_vec, *centroids_curr_vec, *curr_dp;
    curr_dp = dp_head;
    centroids_head_vec = malloc(sizeof(struct vector));
    centroids_curr_vec = centroids_head_vec;
    centroids_curr_vec->next = NULL;

    int i;
    for(i=0; i<k; i++){
        centroids_curr_vec->cords = createVector(curr_dp->cords);
        if(i != (k-1)){
            centroids_curr_vec->next = malloc(sizeof(struct vector));
        }
        centroids_curr_vec = centroids_curr_vec->next;
        if(i != (k-1)){
            centroids_curr_vec->next = NULL;
        }
        curr_dp = curr_dp->next;
    }
    return centroids_head_vec;
}

struct vector* createEmptyCentroids(int k, int size_of_vector){
    struct vector *vec, *curr_vec;

    vec = malloc(sizeof(struct vector));
    curr_vec = vec;
    vec->next = NULL;

    int i;
    for(i = 0; i<k; i++){
        curr_vec->cords = createEmptyCord(size_of_vector);
        if(i != (k-1)){
            curr_vec->next = malloc(sizeof(struct vector));
        }
        curr_vec = curr_vec->next;
        if(i != (k-1)){
            curr_vec->next = NULL;
        }
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
    curr_vec = new_centroid;
    curr_cord = new_centroid->cords;
    int i;
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
    return;
}

void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k){
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
    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;
    curr_cord->value = 0;
    int i;
    for(i=1;i<size_of_vector; i++){
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
        curr_cord->value = 0;
    }
    return head_cord;
}
struct vector* copyOf(struct vector *old_centroid){
    struct vector *new_centroids_head, *curr_vec1, *curr_vec2;
    struct cord *curr_cord1, *curr_cord2;

    new_centroids_head = malloc(sizeof(struct vector));
    curr_vec1 = new_centroids_head;
    curr_vec2 = old_centroid;

    while(curr_vec2 != NULL){
        curr_vec1->cords = createVector(curr_vec2->cords);
        curr_vec1->next = malloc(sizeof(struct vector));
        curr_vec1 = curr_vec1->next;
        curr_vec1->next = NULL;
        if(curr_vec2->next == NULL){
            break;
        }
        curr_vec2 = curr_vec2->next;
    }
    return new_centroids_head;
}