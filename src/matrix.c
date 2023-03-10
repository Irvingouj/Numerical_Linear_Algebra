#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "vector.h"
#include <stdbool.h>
#include "lab1.h"

double get_value(Matrix *self, size_t row, size_t col)
{
    return self->vals[row][col];
}

void set_value(Matrix *self, size_t row, size_t col, double val)
{
    self->vals[row][col] = val;
}
void vector_multiply(Matrix *self, double *vector, double *res)
{
}
// num_of_rows is the number of rows and num_of_columns is the number of columns
void matrix_multiply(Matrix *left, Matrix *right, Matrix *res)
{
    if (left->num_of_columns != right->num_of_rows)
    {
        printf("Matrix dimensions do not match\n");
        return;
    }
    if (res->num_of_rows != left->num_of_rows || res->num_of_columns != right->num_of_columns)
    {
        printf("Result matrix dimensions do not match\n");
        return;
    }

    double *left_row = malloc(sizeof(double) * left->num_of_columns);
    double *right_col = malloc(sizeof(double) * right->num_of_rows);
    for (size_t i = 0; i < res->num_of_rows; ++i)
    {
        for (size_t j = 0; j < res->num_of_columns; ++j)
        {
            double sum = 0;
            left->vtable->get_row(left, i, left_row);
            right->vtable->get_col(right, j, right_col);
            sum = vector_dot_product(left_row, right_col, left->num_of_columns);
            res->vtable->set_value(res, i, j, sum);
        }
    }

    free(left_row);
    free(right_col);
}

void Matrix_destroy(Matrix *self)
{
    free(self->vals);
    free(self->vtable);
    free(self);
}

void get_row(Matrix *self, size_t row, double *res)
{
    for (size_t i = 0; i < self->num_of_columns; i++)
    {
        res[i] = self->vtable->get_value(self, row, i);
    }
}

void get_col(Matrix *self, size_t col, double *res)
{
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        res[i] = self->vtable->get_value(self, i, col);
    }
}

void print(struct Matrix *self)
{
    // print to stdou
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        for (size_t j = 0; j < self->num_of_columns; j++)
        {
            printf("%f, ", self->vtable->get_value(self, i, j));
        }
        printf("\n");
    }
}

void Matrix_init(struct Matrix *self, size_t num_of_rows, size_t num_of_columns)
{
    self->num_of_columns = num_of_columns;
    self->num_of_rows = num_of_rows;

    self->vals = (double **)calloc(self->num_of_rows, sizeof(double *));
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        self->vals[i] = (double *)calloc(num_of_columns, sizeof(double));
    }

    self->vtable = (Matrix_VTable *)malloc(sizeof(Matrix_VTable));
    self->vtable->get_value = &get_value;
    self->vtable->vector_multiply = &vector_multiply;
    self->vtable->set_value = &set_value;
    self->vtable->print = &print;
    self->vtable->matrix_multiply = &matrix_multiply;
    self->vtable->get_row = &get_row;
    self->vtable->get_col = &get_col;
}

void Matrix_multiply_left_transpose(Matrix *left, Matrix *right, Matrix *res)
{
    if (left->num_of_rows != right->num_of_rows)
    {
        printf("Matrix dimensions do not match\n");
        abort();
        return;
    }
    if (res->num_of_rows != left->num_of_columns || res->num_of_columns != right->num_of_columns)
    {
        printf("Result matrix dimensions do not match\n");
        abort();
        return;
    }

    double *left_row = malloc(sizeof(double) * left->num_of_rows);
    double *right_col = malloc(sizeof(double) * right->num_of_rows);
    for (size_t i = 0; i < res->num_of_rows; ++i)
    {
        for (size_t j = 0; j < res->num_of_columns; ++j)
        {
            double sum = 0;
            left->vtable->get_col(left, i, left_row);
            right->vtable->get_col(right, j, right_col);
            sum = vector_dot_product(left_row, right_col, left->num_of_rows);
            res->vtable->set_value(res, i, j, sum);
        }
    }

    free(left_row);
    free(right_col);
}

void Matrix_multiply_right_transpose(Matrix *left, Matrix *right, Matrix *res)
{
    if (left->num_of_columns != right->num_of_columns)
    {
        printf("Matrix dimensions do not match\n");
        return;
    }
    if (res->num_of_rows != left->num_of_rows || res->num_of_columns != right->num_of_rows)
    {
        printf("Result matrix dimensions do not match\n");
        return;
    }

    double *left_row = malloc(sizeof(double) * left->num_of_columns);
    double *right_col = malloc(sizeof(double) * right->num_of_columns);
    for (size_t i = 0; i < res->num_of_rows; ++i)
    {
        for (size_t j = 0; j < res->num_of_columns; ++j)
        {
            double sum = 0;
            left->vtable->get_row(left, i, left_row);
            right->vtable->get_row(right, j, right_col);
            sum = vector_dot_product(left_row, right_col, left->num_of_columns);
            res->vtable->set_value(res, i, j, sum);
        }
    }

    free(left_row);
    free(right_col);
}

void Matrix_multiply(Matrix *left, Matrix *right, Matrix *res)
{
    matrix_multiply(left, right, res);
}

Matrix *New_Matrix_from_array(double **array, size_t num_of_rows, size_t num_of_columns)
{
    Matrix *res = New_Matrix_row_col(num_of_rows, num_of_columns);
    for (size_t i = 0; i < num_of_rows; i++)
    {
        for (size_t j = 0; j < num_of_columns; j++)
        {
            res->vtable->set_value(res, i, j, array[i][j]);
        }
    }
    return res;
}

Matrix *New_Matrix_row_col(size_t num_of_rows, size_t num_of_columns)
{
    Matrix *res = (Matrix *)malloc(sizeof(Matrix));
    Matrix_init(res, num_of_rows, num_of_columns);
    return res;
}

bool is_square(Matrix *self)
{
    return self->num_of_rows == self->num_of_columns;
}
bool is_lower_triangular(Matrix *self)
{
    if (!is_square(self))
    {
        return false;
    }
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        for (size_t j = i + 1; j < self->num_of_columns; j++)
        {
            if (self->vtable->get_value(self, i, j) != 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool can_multiply(Matrix *self, Matrix *other)
{
    return self->num_of_columns == other->num_of_rows;
}
bool can_solve(Matrix *self, size_t b_size)
{
    return self->num_of_rows == b_size;
}
bool is_upper_triangular(Matrix *self)
{
    if (!is_square(self))
    {
        return false;
    }
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (self->vtable->get_value(self, i, j) != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void Matrix_copy(Matrix *self, Matrix *other)
{
    if (self->num_of_rows != other->num_of_rows || self->num_of_columns != other->num_of_columns)
    {
        printf("Matrices do not match\n");
        return;
    }
    for (size_t i = 0; i < self->num_of_rows; i++)
    {
        for (size_t j = 0; j < self->num_of_columns; j++)
        {
            self->vtable->set_value(self, i, j, other->vtable->get_value(other, i, j));
        }
    }
}

void QR_Factorization(Matrix *A, Matrix *Q, Matrix *R)
{
    if (!can_multiply(Q, R))
    {
        printf("Matrices do not match\n");
        exit(2);
        return;
    }
    if (!is_square(R) || R->num_of_rows != A->num_of_columns)
    {
        printf("Matrices do not match\n");
        exit(2);
        return;
    }

    Matrix *temp = GramSchmidt(A);
    Matrix_copy(Q, temp);

    free(temp);

    for (size_t i = 0; i < R->num_of_rows; i++)
    {
        for (size_t j = 0; j < R->num_of_columns; j++)
        {
            if (i > j)
            {
                R->vtable->set_value(R, i, j, 0);
            }
            else
            {
                double *a_j = calloc(Q->num_of_rows, sizeof(double));
                double *e_i = calloc(A->num_of_rows, sizeof(double));
                A->vtable->get_col(A, j, a_j);
                Q->vtable->get_col(Q, i, e_i);

                double val = vector_dot_product(a_j, e_i, Q->num_of_rows);
                R->vtable->set_value(R, i, j, val);

                free(a_j);
                free(e_i);
            }
        }
    }
}