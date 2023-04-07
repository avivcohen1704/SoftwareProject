#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "spkmeans.h"


void ll_to_arr_spk(int num_of_dp, int size_of_vec, struct vector *dp_head, double **res);/*res dim is num_of_dp*size_of_vec*/ 
void output_print(int n ,double **matrix);/*matrix n*n*/
void output_print_j(int n ,double **matrix);/*matrix n+1*n*/
int input_valid(int argc, char **argv);
void create_matrix_s(int n, int m, double **matrix);



int main(int argc, char **argv){
    struct vector *dp_head, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int num_of_dp, size_of_vec;
    double n;
    char c;
    double **input_array = NULL;

    if(input_valid(argc,argv)){
        printf("An Error Has Occurred");
        return 1;
    }
    

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
    
    
    size_of_vec++;
    create_matrix_s(num_of_dp,size_of_vec,input_array); /*added this line*/

    free(head_cord);
    
    ll_to_arr_spk(num_of_dp,size_of_vec,dp_head,input_array);


    if (strcmp(argv[1], "wam") == 0){
        double **output_array = NULL;
        create_matrix_s(num_of_dp,num_of_dp,output_array); /*added this line*/
        wam_c(num_of_dp, size_of_vec, input_array, output_array);
        output_print(num_of_dp, output_array);

    }

    if (strcmp(argv[1], "ddg") == 0){
        double **wam_output = NULL;
        double **output_array = NULL;
        create_matrix_s(num_of_dp,num_of_dp,wam_output); /*added this line*/
        create_matrix_s(num_of_dp,num_of_dp,output_array); /*added this line*/
        wam_c(num_of_dp,size_of_vec,input_array, wam_output);
        ddg_c(num_of_dp, wam_output, output_array);
        output_print(num_of_dp, output_array);
    }
    
    if (strcmp(argv[1], "gl") == 0){
        double **wam_output = NULL;
        double **ddg_output = NULL;
        double **output_array = NULL;
        create_matrix_s(num_of_dp,num_of_dp,wam_output); /*added this line*/
        create_matrix_s(num_of_dp,num_of_dp,ddg_output); /*added this line*/
        create_matrix_s(num_of_dp,num_of_dp,output_array); /*added this line*/
        wam_c(num_of_dp, size_of_vec,input_array, wam_output);
        ddg_c(num_of_dp, wam_output, ddg_output);
        gl_c(num_of_dp, ddg_output,wam_output,output_array);
        output_print(num_of_dp, output_array);
    }

    if (strcmp(argv[1], "jacobi") == 0){
        double **output_array = NULL;
        create_matrix_s(num_of_dp+1,num_of_dp,output_array); /*added this line, here the size is n_o_d+1*n_o_d*/
        jacobi_c(num_of_dp, input_array, output_array);
        output_print_j(num_of_dp, output_array);

    }
    return 1;
}

void output_print(int n ,double **matrix){
    int i,j;
    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%.4f" , matrix[i][j]);
            printf(",");
        }
        printf("\n");
    }
}


void output_print_j(int n ,double **matrix){
    /* we might change this to matrix = matrix.transpose */
    int i,j;
    for (j=0;j<n;j++){
        printf("%.4f" , matrix[n+1][j]);
        printf(",");
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
    int i,s;
    char funcs[4][10] = {"wam","ddg" , "gl" , "jacobi"};
    s =0;
    
    if(argc!=3){
        return 1;
    }
    for (i=0;i<4;i++){
        if (strcmp(argv[1], funcs[i]) == 0){
            s = s+1;
        }
    }
    if (s == 0){
        
        return 1;
    }
    return 0;
}


void ll_to_arr_spk(int num_of_dp, int size_of_vec, struct vector *dp_head, double **res){ 
    struct vector *curr_vec;
    struct cord *curr_cord;
    int i,j;
    
    curr_vec = dp_head;
    for (i = 0; i < num_of_dp; i++){
        curr_cord = curr_vec->cords;
        for (j = 0; j < size_of_vec; j++){
            res[i][j] = curr_cord->value;
            curr_cord = curr_cord->next;
        }
        curr_vec = curr_vec->next;
    }
}

void create_matrix_s(int n, int m, double **matrix){
    int i;
    matrix = (double**)calloc(n, sizeof(double*));
    for(i=0;i<n;i++){
        matrix[i] = (double*)calloc(m, sizeof(double));
    }
}
