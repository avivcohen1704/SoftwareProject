# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

double e = 0.001;
int inputValidation(int k, int iter, int num_of_dp);
struct vector *getCentroids(struct vector *dp_head, int k);
struct cord* createVector(struct cord *x);
void kmeans(struct vector *dp_head, struct vector *centroids_head_vec,int k, int iter, int num_of_dp);
struct vector* createEmptyCentroids(int k, int size_of_vector);
double euclideanDistance(struct cord *x1, struct cord *x2);
int getCordLength(struct vector *dp_head);
void divide_centroid(struct vector *new_centroid,int num_of_dp_in_cluster[],int k);
void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k);
void addCords(struct cord *curr_cord1, struct cord *min_cord);
void create_Array(int array[], int len);
struct cord* createEmptyCord(int size_of_vector);
struct vector* copyOf(struct vector *old_centroid);
void freeSpaceCord(struct cord *Cord);
void freeSpaceVec(struct vector *vec);
int isNum (char *s);
int isDigit(char c);

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
    struct vector *centroids_head_vec;
    char *s;

    if(argc>3){
        printf("An Error Has Occurred");
        return 0;
    }
    if(argc<2){
        printf("An Error Has Occurred");
    }

    s = argv[1];
    if(isNum(s)==0){
        printf("Invalid number of centroids!");
        return 0;
    }

    k = atoi(argv[1]);

    if((argv[2]) == NULL ){
        iter = 200;
    }
    else{
        if(isNum(argv[2]) == 0){
            printf("Invalid maximun iteration!");
            return 0;
        }
        iter = atoi(argv[2]);
    }


    head_cord = calloc(1,sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    dp_head = calloc(1,sizeof(struct vector));
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
            curr_vec->next = calloc(1,sizeof(struct vector));
            curr_vec = curr_vec->next;
        
            curr_vec->next = NULL;
            head_cord = calloc(1,sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }


        curr_cord->value = n;
        curr_cord->next = calloc(1,sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;


    }
     
    free(head_cord);

    if (inputValidation(k, iter, num_of_dp)){
        freeSpaceVec(dp_head);/*dnf*/
        return 0;
    }
    

    centroids_head_vec = getCentroids(dp_head, k);



    kmeans(dp_head, centroids_head_vec, k, iter, num_of_dp);

    return 0;
}

void kmeans(struct vector *dp_head, struct vector *old_centroids_head_vec,int k, int iter, int num_of_dp){

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
        printf("\nthe iteration is:%d",iterCNT);

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
        check_converge(new_head_vec, head_vec2, convergence_array, k);
        cnt = 0;
        for (l=0; l<k; l++){
            if(convergence_array[l]==1){
                int val = convergence_array[l];
                cnt+=1;
            }
        }
        convergenceCNT = cnt;
        iterCNT +=1;

       

        freeSpaceVec(head_vec2);
        curr_vec2 = copyOf(new_head_vec);
        head_vec2 = curr_vec2;



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

    freeSpaceVec(head_vec2);
    freeSpaceVec(dp_head);
    freeSpaceVec(new_head_vec);
    free(convergence_array);
    free(num_of_dp_in_cluster);

}


int inputValidation(int k, int iter, int num_of_dp){
    /*if((k<=1) || (k>=num_of_dp) || (k%1 !=0)){
        printf("Invalid number of clusters!");
        return 1;
    }
    if((iter <= 1) || (iter >= 1000) || (iter % 1 != 0)) {
        printf("Invalid maximum iteration!");
        return 1;
    }*/
    return 0;
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

struct vector *getCentroids(struct vector *dp_head, int k){

    /*decleration & init of centroids struct*/
    struct vector *centroids_head_vec, *centroids_curr_vec, *curr_dp;
    int i;

    curr_dp = dp_head;
    centroids_head_vec = calloc(1,sizeof(struct vector));
    centroids_curr_vec = centroids_head_vec;
    centroids_curr_vec->next = NULL;

    for(i=0; i<k; i++){
        centroids_curr_vec->cords = createVector(curr_dp->cords);
        if(i != (k-1)){
            centroids_curr_vec->next = calloc(1,sizeof(struct vector));
            centroids_curr_vec = centroids_curr_vec->next;
            centroids_curr_vec->next = NULL;
            curr_dp = curr_dp->next; 
        }
    }
    return centroids_head_vec;
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

void check_converge(struct vector *new_head_vec, struct vector *head_vec1, int convergence_array[], int k){
    int i;
    
    struct vector *curr_vec1, *curr_vec2;
    curr_vec1 = new_head_vec;
    curr_vec2 = head_vec1;
    

    for(i=0; i<k; i++){
        if(convergence_array[i]==1){
            continue;
        }
        
        float d = euclideanDistance(curr_vec1->cords,curr_vec2->cords);
        if(d < e){
            convergence_array[i] = 1;
        }
        curr_vec1 = curr_vec1->next;
        curr_vec2 = curr_vec2->next;
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
