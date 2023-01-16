#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef enum RANDOM_MODE
{
    A,
    B,
    C,
    D
} RANDOM_MODE;
typedef struct Matrix Matrix;

typedef struct Matrix_VTable
{
    double (*get_value)(Matrix *self, size_t row, size_t col);
    void (*vector_multiply)(Matrix *self, double *vector, double *res);
    void (*set_value)(Matrix *self, size_t row, size_t col, double val);
    void (*print)(Matrix *self);
} Matrix_VTable;

typedef struct Matrix
{
    size_t row_size;
    size_t col_size;
    double *vals;
    Matrix_VTable *vtable;
} Matrix;

int create_matrix_csr(
    Matrix *mat,
    size_t n_rows,
    size_t n,
    double *vals
    );

extern void Matrix_init(struct Matrix *self, size_t row_size, size_t col_size);
extern Matrix* New_Matrix(size_t row_size,size_t col_size);
extern void Matrix_destroy(struct Matrix *self);

#endif
