#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


double get_value(Matrix *self, size_t row, size_t col){
    return self->vals[self->row_size*row + col];
}

void set_value(Matrix *self, size_t row, size_t col, double val){
    self->vals[self->row_size*row + col] = val;
}
void vector_multiply(Matrix *self, double *vector, double *res){

}
void Matrix_destroy(Matrix *self){
    free(self->vals);
    free(self->vtable);
    free(self);
}

void print(struct Matrix *self){
    //print to stdou 
    for (size_t i = 0; i < self->row_size; i++)
    {
        for (size_t j = 0; j < self->col_size; j++)
        {
            printf("%f, ", self->vtable->get_value(self, i, j));
        }
        printf("\n");
    }
}

void Matrix_init(struct Matrix *self, size_t row_size, size_t col_size){
    self->row_size = row_size;
    self->col_size = col_size;
    self->vals = malloc(row_size*col_size*sizeof(double));
    //set all value to zero
    for(size_t i = 0; i < row_size*col_size; i++)
        self->vals[i] = 0.0;
        
    self->vtable = (Matrix_VTable*)malloc(sizeof(Matrix_VTable));
    self->vtable->get_value = &get_value;
    self->vtable->vector_multiply = &vector_multiply;
    self->vtable->set_value = &set_value;
    self->vtable->print = &print;
}

Matrix* New_Matrix(size_t row_size,size_t col_size){
    Matrix* res = (Matrix*)malloc(sizeof(Matrix));
    Matrix_init(res, row_size, col_size);
    return res;
}