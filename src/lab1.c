#include "matrix.h"
#include <stdlib.h>

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
    Matrix *res = New_Matrix(n, n);
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
    Matrix *res = New_Matrix(n, n);

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
    Matrix *res = New_Matrix(n, n);
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
    Matrix *res = New_Matrix(n, n);
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
Matrix *MatRand(size_t n, size_t m, double p) { 
    Matrix *res = New_Matrix(n, m);
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            double val = get_random_double_range(p,-p);
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};

// problem 2
Matrix *ProductMatrix(Matrix *B, Matrix *c) {
    // check if B and c are compatible
    if (B->col_size != c->row_size)
    {
        return NULL;
    }

    Matrix *res = New_Matrix(B->row_size, c->col_size);
    for (size_t i = 0; i < B->row_size; i++)
    {
        for (size_t j = 0; j < c->col_size; j++)
        {
            double val = 0;
            for (size_t k = 0; k < B->col_size; k++)
            {
                val += B->vtable->get_value(B, i, k) * c->vtable->get_value(c, k, j);
            }
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};

double Trans(Matrix *A) {
    double res = 0;
    // sum up diagonal
    for (size_t i = 0; i < A->row_size; i++)
    {
        res += A->vtable->get_value(A, i, i);
    }

    return res;
}

Matrix *GramSchmidt(Matrix *A) { 
    // check if A is square
    if (A->row_size != A->col_size)
    {
        return NULL;
    }

    Matrix *res = New_Matrix(A->row_size, A->col_size);
    for (size_t i = 0; i < A->row_size; i++)
    {
        for (size_t j = 0; j < A->col_size; j++)
        {
            double val = A->vtable->get_value(A, i, j);
            for (size_t k = 0; k < i; k++)
            {
                double val2 = res->vtable->get_value(res, k, j);
                val -= val2 * res->vtable->get_value(res, k, i);
            }
            res->vtable->set_value(res, i, j, val);
        }
    }

    return res;
};