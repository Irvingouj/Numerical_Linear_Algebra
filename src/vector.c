#include "vector.h"
#include <math.h>
#include <stdlib.h>
#include "matrix.h"

void vector_add(double *a, double *b, size_t n, double *res)
{
    for (size_t i = 0; i < n; i++)
    {
        res[i] = a[i] + b[i];
    }
}

void vector_subtract(double *a, double *b, size_t n, double *res){
    for (size_t i = 0; i < n; i++)
    {
        res[i] = a[i] - b[i];
    }
}

double vector_dot_product(double *a, double *b, size_t n){
    double res = 0;
    for (size_t i = 0; i < n; i++)
    {
        res += a[i] * b[i];
    }
    return res;
}

void vector_scalar_multiply(double *a, double b, size_t n, double *res){
    for (size_t i = 0; i < n; i++)
    {
        res[i] = a[i] * b;
    }
}

void vector_copy(double *a, size_t n, double *res){
    for (size_t i = 0; i < n; i++)
    {
        res[i] = a[i];
    }
}

double vector_norm(double *a, size_t n)
{
    return sqrt(vector_dot_product(a, a, n));
}

double** matrix_to_col(Matrix* A){
    double** res = init_2d_array(A->col_size, A->row_size);
    // for each column in A
    for(size_t i = 0; i< A->row_size; i++){
        for (size_t j = 0; j < A->col_size; j++)
        {
            res[i][j] = A->vtable->get_value(A, j, i);
        }
        
    }
    return res;
}

double** init_2d_array(size_t size_sigle_vector, size_t size_of_collection){
    double** res = (double**)calloc(size_of_collection,sizeof(double*));
    for(size_t i = 0; i < size_of_collection; i++){
        res[i] = (double*)calloc(size_sigle_vector,sizeof(double));
    }
    return res;
}

void free_double_pointer(double** vectors, size_t n){
    for(size_t i = 0; i < n; i++){
        free(vectors[i]);
    }
    free(vectors);
}


double* New_Vector(size_t n){
    double* res = (double*)calloc(n,sizeof(double));
    return res;
}

void projection(double *u,double *v, size_t n, double *res){

    double proj_coeff = vector_dot_product(u, v, n) / vector_dot_product(u, u, n);
    printf("proj_coeff: %f \n", proj_coeff);
    vector_scalar_multiply(u, proj_coeff, n, res);
}

void vector_normalize(double *u, size_t n){
    double norm = vector_norm(u, n);
    vector_scalar_multiply(u, 1/norm, n, u);
}

void print_vector(double* v, size_t n,char* name){
    printf("Vector %s: [",name);
    for (size_t i = 0; i < n; i++)
    {
        printf("%f ", v[i]);
    }
    printf("] \n");
};



