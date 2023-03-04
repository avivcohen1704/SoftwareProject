#include <Python.h>
#include <spkeamns.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>

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

int main(int argc, char **argv){
    if(input_valid(argc,argv)){
        printf("An Error Has Occurred");
        return 1;
    }
    struct vector *dp_head, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int num_of_dp, size_of_vec;

    size_of_vec = 0;
    num_of_dp = 0;

    head_cord = calloc(1,sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    dp_head = calloc(1,sizeof(struct vector));
    curr_vec = dp_head;
    curr_vec->next = NULL;


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

        if(num_of_dp == 0){
            size_of_vec++;
        }
        curr_cord->value = n;
        curr_cord->next = calloc(1,sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;


    }
    double [num_of_dp][size_of_vec] input_array;
    
    free(head_cord);
    input_array = ll_to_arr(num_of_dp,size_of_vec,dp_head);

    if (argv[1] == "wam"){
        double [num_of_dp][num_of_dp] output_array;
        output_array = wam(num_of_dp,input_array);
        output_print(num_of_dp, output_array);

    }

    if (argv[1] == "ddg"){
        double [num_of_dp][num_of_dp] output_array;
        output_array = ddg(num_of_dp,input_array);
        output_print(num_of_dp, output_array);
    }
    
    if (argv[1] == "gl"){
        double [num_of_dp][num_of_dp] output_array;
        output_array = gl(num_of_dp,input_array);
        output_print(num_of_dp, output_array);
    }

    if (argv[1] == "jacobi"){
        double [num_of_dp+1][num_of_dp] output_array;
        output_array = jacobi(num_of_dp,input_array);
        output_print_j(num_of_dp, output_array);

    }


}

void output_print(n ,double[n][n] matrix){
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%.4f" , matrix[i][j]);
            printf(",");
        }
        printf("\n");
    }
}


void output_print_j(n ,double[n+1][n] matrix){
    /* we might change this to matrix = matrix.transpose */
    int i,j;
    for (j=0;j<n;j++){
        printf("%.4f" , matrix[n+1][j]);
    }

    printf("\n");

    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%.4f" , matrix[i][j]);
            printf(",");
        }
        printf("\n");
    }
}


int input_valid(int argc, char **argv){
    char[4] funcs;
    int i,s;
    s =0;
    
    if(argc!=3){
        return 1;
    }
    funcs = ["wam","ddg" , "gl" , "jacobi"];
    for (i=0;i<4;i++){
        if (argv[1] == funcs[i]){
            s = s+1;
        }
    }
    if (s == 0){
        return 1;
    }
    return 0;
}


double** ll_to_arr(int num_of_dp, int size_of_vec, struct vector *dp_head){
    struct vector *curr_vec;
    struct cord *curr_cord;
    int i,j;
    double [num_of_dp][size_of_vec] res;

    curr_vec = dp_head;
    for (i=0;i<num_of_dp;i++){
        curr_cord = curr_vec->cords;
        for (j=0;j<size_of_vec; j++){
            res[i][j] = curr_cord->value;
            curr_cord = curr_cord->next;
        }
        curr_vec = curr_vec->next;
    }
    return res;
}
