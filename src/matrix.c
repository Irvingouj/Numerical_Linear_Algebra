#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


double get_value(struct Matrix *self, size_t row, size_t col){
    return self->vals[self->row_size*row + col];
}

void vector_multiply(struct Matrix *self, double *vector, double *res){

}
void Matrix_destroy(struct Matrix *self){
    free(self->vals);
    free(self->vtable);
}

void Matrix_init(struct Matrix *self, size_t row_size, size_t col_size){
    self->row_size = row_size;
    self->col_size = col_size;
    self->vals = malloc(row_size*col_size*sizeof(double));
    self->vtable = (Matrix_VTable*)malloc(sizeof(Matrix_VTable));
    self->vtable->get_value = &get_value;
    self->vtable->vector_multiply = &vector_multiply;
}

Matrix* New_Matrix(size_t row_size,size_t col_size){
    Matrix* res = (Matrix*)malloc(sizeof(Matrix));
    res->row_size = row_size;
    res->col_size = col_size;
    res->vals = malloc(row_size*col_size*sizeof(double));
    res->vtable = (Matrix_VTable*)malloc(sizeof(Matrix_VTable));
    res->vtable->get_value = &get_value;
    res->vtable->vector_multiply = &vector_multiply;
    return res;
}