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
    Matrix_multiply(left, right, res);
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
    for (size_t i = 0; i < res->num_of_rows; i++)
    {
        vector_normalize(Us[i], vec_n);
        
        for (size_t j = 0; j < res->num_of_columns; j++)
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

void Problem_1(){
    printf("Problem 1 test\n\n");

    Matrix *m = New_Matrix_row_col(5, 5);
    int counter = 0;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = i; j < 5; j++)
        {
            m->vtable->set_value(m, i, j, ++counter);
        }
    }

    m->vtable->print(m);

    printf("\nProblem 1 MatSym\n");
    Matrix *m1 = MatSym(5);
    m1->vtable->print(m1);
    Matrix_destroy(m1);

    printf("\n MatReg ------------------\n");
    Matrix *m2 = MatReg(5);
    m2->vtable->print(m2);
    Matrix_destroy(m2);

    printf("\nMatRegI ------------------\n");
    Matrix *m3 = MatRegI(5);
    m3->vtable->print(m3);
    Matrix_destroy(m3);

    printf("\nMatRegU ------------------\n");
    Matrix *m4 = MatRegU(5);
    m4->vtable->print(m4);
    Matrix_destroy(m4);

    printf("\nMatRand ------------------\n");
    Matrix *m5 = MatRand(3, 4, 5);
    m5->vtable->print(m5);
    Matrix_destroy(m5);


    

    

}

void Problem_2(){
    printf("Problem 2 test\n");

    printf("\nProblem 2 ProductMatrix\n");
    Matrix *b = New_Matrix_row_col(3, 3);
    // init b to identity matrix
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
            {
                b->vtable->set_value(b, i, j, 1);
            }
        }
    }

    Matrix *c = MatReg(3);
    Matrix *a = ProductMatrix(b, c);
    // print a b and c with print function
    printf("\n a \n");
    a->vtable->print(a);
    printf("\n b \n");
    b->vtable->print(b);
    printf("\n c \n");
    c->vtable->print(c);

    Matrix_destroy(a);
    Matrix_destroy(b);
    Matrix_destroy(c);

    printf("\nProblem 2 Trans\n");
    Matrix *m6 = MatReg(5);
    double transpos = Trans(m6);
    printf("transpos = %f\n", transpos);
    m6->vtable->print(m6);
    Matrix_destroy(m6);   

}
void Problem_3(){
    double val[2][2] = {{1, 2}, {3, 4}};
    
    Matrix *A = New_Matrix_row_col(2, 2);
    for (size_t i = 0; i < A->num_of_rows; i++)
    {
        for (size_t j = 0; j < A->num_of_columns; j++)
        {
            A->vtable->set_value(A, i, j, val[i][j]);
        }
    }

    printf("A:\n");
    A->vtable->print(A);

    Matrix* U = GramSchmidt(A);
    printf("U:\n");
    U->vtable->print(U);

    Matrix* UU_t = New_Matrix_row_col(U->num_of_rows, U->num_of_rows);
    Matrix_multiply_right_transpose(U, U,UU_t);
    printf("U multiply by U Trasnpose:\n");
    UU_t->vtable->print(UU_t);

    Matrix* U_tU = New_Matrix_row_col(U->num_of_columns, U->num_of_columns);
    Matrix_multiply_left_transpose(U, U, U_tU);
    printf("U Trasnpose multiply by U:\n");
    U_tU->vtable->print(U_tU);

    Matrix* U_tA = New_Matrix_row_col(U->num_of_columns, A->num_of_columns);
    Matrix_multiply_left_transpose(U, A, U_tA);
    printf("U Trasnpose multiply by A:\n");
    U_tA->vtable->print(U_tA);


    //destroy all matrix
    Matrix_destroy(A);
    Matrix_destroy(U);
    Matrix_destroy(UU_t);
    Matrix_destroy(U_tU);
    Matrix_destroy(U_tA);
}

void Problem_3_3By3(){
    // do problem 3 again with 3 by 3 matrix
    double val[3][3] = {{2, 1, 0},
                        {0, 1, 1},
                        {0, 2, -1}};
    Matrix *A = New_Matrix_row_col(3, 3);
    for (size_t i = 0; i < A->num_of_rows; i++)
    {
        for (size_t j = 0; j < A->num_of_columns; j++)
        {
            A->vtable->set_value(A, i, j, val[i][j]);
        }
    }

    printf("A:\n");
    A->vtable->print(A);

    Matrix* U = GramSchmidt(A);
    printf("U:\n");
    U->vtable->print(U);


    Matrix* UU_t = New_Matrix_row_col(U->num_of_rows, U->num_of_rows);
    Matrix_multiply_right_transpose(U, U,UU_t);
    printf("U multiply by U Trasnpose:\n");
    printf("U multiply by U Trasnpose will give identity matrix \n");
    UU_t->vtable->print(UU_t);

    Matrix* U_tU = New_Matrix_row_col(U->num_of_columns, U->num_of_columns);
    Matrix_multiply_left_transpose(U, U, U_tU);
    printf("U Trasnpose multiply by U:\n");
    U_tU->vtable->print(U_tU);

    Matrix* U_tA = New_Matrix_row_col(U->num_of_columns, A->num_of_columns);
    Matrix_multiply_left_transpose(U, A, U_tA);
    printf("U Trasnpose multiply by A:\n");
    printf("U Trasnpose multiply by A will give a upper triangular matirx\n");
    U_tA->vtable->print(U_tA);

    //destroy all matrix
    Matrix_destroy(A);
    Matrix_destroy(U);
    Matrix_destroy(UU_t);
    Matrix_destroy(U_tU);


}