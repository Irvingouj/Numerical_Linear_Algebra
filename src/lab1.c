#include "matrix.h"
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include <string.h>

// generate randowm double
double get_random_double()
{
    return (double)rand() / (double)RAND_MAX;
}
double get_random_double_range(double min, double max)
{
    return min + (max - min) * get_random_double();
}
Matrix *MatSym(size_t n)
{
    Matrix *res = New_Matrix_row_col(n, n);
    // generate random symatric matrix
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            double val = get_random_double();
            res->vtable->set_value(res, i, j, val);
            res->vtable->set_value(res, j, i, val);
        }
    }
    return res;
}
Matrix *MatReg(size_t n)
{
    Matrix *res = New_Matrix_row_col(n, n);

    // upper triangular matrix with diagonal non zero, hence must be invertible
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            double val = get_random_double();
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};
Matrix *MatRegI(size_t n)
{
    // real lower triangular invertible matrix, non zero diagonal, hence invertible
    Matrix *res = New_Matrix_row_col(n, n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j <= i; j++)
        {
            double val = get_random_double();
            res->vtable->set_value(res, i, j, val);
        }
    }
    return res;
};
Matrix *MatRegU(size_t n)
{
    // same as MatReg
    Matrix *res = New_Matrix_row_col(n, n);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i; j < n; j++)
        {
            double val = get_random_double();
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};
Matrix *MatRand(size_t num_of_row, size_t num_of_col, double p)
{
    Matrix *res = New_Matrix_row_col(num_of_row, num_of_col);
    for (size_t i = 0; i < res->num_of_rows; i++)
    {
        for (size_t j = 0; j < res->num_of_columns; j++)
        {
            double val = get_random_double_range(p, -p);
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};

// problem 2
Matrix *ProductMatrix(Matrix *left, Matrix *right)
{
    // check if B and c are compatible
    if (left->num_of_columns != right->num_of_rows)
    {
        printf("Incompatible matrix\n");
        return NULL;
    }

    Matrix *res = New_Matrix_row_col(left->num_of_rows, right->num_of_columns);
    left->vtable->matrix_multiply(left, right, res);
    return res;
}

double Trans(Matrix *A)
{
    // check if it is square
    if (A->num_of_columns != A->num_of_rows)
    {
        return 0;
    }
    double res = 0;
    // sum up diagonal
    for (size_t i = 0; i < A->num_of_columns; i++)
    {
        res += A->vtable->get_value(A, i, i);
    }

    return res;
}

Matrix *GramSchmidt(Matrix *A)
{
    // check if A is square
    if (A->num_of_columns != A->num_of_rows)
    {
        return NULL;
    }
    const size_t vec_n = A->num_of_rows;

    // set ups
    Matrix *res = New_Matrix_row_col(A->num_of_rows, A->num_of_columns);
    double **Vs = matrix_to_col(A);
    double **Us = init_2d_array(vec_n, A->num_of_columns);

    // gram schmidt
    vector_copy(Vs[0], vec_n, Us[0]);
    for (int k = 1; k < A->num_of_columns; k++)
    {
        double *proj = (double *)calloc(sizeof(double), vec_n);
        double *temp = (double *)calloc(sizeof(double), vec_n);
        for (int j = 0; j < k; j++)
        {
            projection(Us[j], Vs[k], vec_n, temp);
            vector_add(proj, temp, vec_n, proj);
        }
        vector_subtract(Vs[k], proj, vec_n, Us[k]);

        free(temp);
        free(proj);
    }

    // build res from normalized Us
    for (size_t i = 0; i < A->num_of_columns; i++)
    {
        vector_normalize(Us[i], vec_n);
        for (size_t j = 0; j < vec_n; j++)
        {
            res->vtable->set_value(res, i, j, Us[i][j]);
        }
    }

    // free
    free_double_pointer(Vs, A->num_of_columns);
    free_double_pointer(Us, A->num_of_columns);

    // remember to free
    return res;
};
