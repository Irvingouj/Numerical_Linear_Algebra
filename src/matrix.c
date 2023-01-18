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
// col_size is the number of rows and row_size is the number of columns
void matrix_multiply(Matrix *self, Matrix *other, Matrix *res){
    //check if other and self are compatible
    if (self->row_size != other->col_size){
        return;
    }
    //check if res is the right size
    if (res->row_size != self->row_size || res->col_size != other->col_size){
        return;
    }

    for (size_t i = 0; i < self->row_size; i++)
    {
        for (size_t j = 0; j < other->col_size; j++)
        {
            double val = 0;
            for (size_t k = 0; k < self->col_size; k++)
            {
                val += self->vtable->get_value(self, i, k) * other->vtable->get_value(other, k, j);
            }
            res->vtable->set_value(res, i, j, val);
        }
    }
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
    self->vals = calloc(row_size*col_size,sizeof(double));
    self->vtable = (Matrix_VTable*)malloc(sizeof(Matrix_VTable));
    self->vtable->get_value = &get_value;
    self->vtable->vector_multiply = &vector_multiply;
    self->vtable->set_value = &set_value;
    self->vtable->print = &print;
}

void Matrix_multiply_left_transpos(Matrix *left,Matrix *right, Matrix *res){
}

void Matrix_multiply_right_transpos(Matrix *left,Matrix *right, Matrix *res){

}

Matrix* New_Matrix(size_t row_size,size_t col_size){
    Matrix* res = (Matrix*)malloc(sizeof(Matrix));
    Matrix_init(res, row_size, col_size);
    return res;
}