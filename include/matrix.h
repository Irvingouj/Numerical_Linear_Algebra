#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef struct Matrix Matrix;

typedef struct Matrix_VTable
{
    double (*get_value)(Matrix *self, size_t row, size_t col);
    void (*vector_multiply)(Matrix *self, double *vector, double *res);
    void (*set_value)(Matrix *self, size_t row, size_t col, double val);
    void (*print)(Matrix *self);
    void (*matrix_multiply)(Matrix *self, Matrix *other, Matrix *res);
    void (*get_row)(Matrix *self, size_t row, double *res);
    void (*get_col)(Matrix *self, size_t col, double *res);
} Matrix_VTable;

typedef struct Matrix
{
    size_t num_of_columns;
    size_t num_of_rows;
    double **vals;
    Matrix_VTable *vtable;
} Matrix;

int create_matrix_csr(
    Matrix *mat,
    size_t n_rows,
    size_t n,
    double *vals
    );

extern void Matrix_init(struct Matrix *self, size_t row_size, size_t col_size);
extern Matrix* New_Matrix_row_col(size_t row_size,size_t col_size);
extern void Matrix_destroy(struct Matrix *self);
extern void Matrix_multiply(Matrix *self, Matrix *other, Matrix *res);
extern void Matrix_multiply_left_transpose(Matrix *left, Matrix *right, Matrix *res);
extern void Matrix_multiply_right_transpose(Matrix *left, Matrix *right, Matrix *res);
extern Matrix* New_Matrix_from_array(double **vals, size_t row_size, size_t col_size);

#endif
