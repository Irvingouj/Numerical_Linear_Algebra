#include <stdio.h>
#include "include/lab1.h"
#include "include/matrix.h"

int main(int argc, char const *argv[])
{

    printf("Matrix Get Test \n");

    Matrix *m = New_Matrix(5, 5);
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


    printf("\nProblem 2 ProductMatrix\n");
    Matrix *b = New_Matrix(3, 3);
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

    printf("\n Problem 3 GramSchmidt\n");




    return 0;
}