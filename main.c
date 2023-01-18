#include <stdio.h>
#include "include/lab1.h"
#include "include/matrix.h"
#include "include/vector.h"

void vector_test();
void gram_schmidt_test();
void matrix_test();
void matrix_multiply_test();

int main(int argc, char const *argv[])
{
    matrix_test();
    // gram_schmidt_test();

    return 0;
}

void gram_schmidt_test(){
    printf("\n Problem 3 GramSchmidt\n");
    Matrix *m7 = New_Matrix_row_col(3, 3);
    double arr[3][3] = {
        {1, 1, 0},
        {0, 2, 2},
        {0, 0, 2}
    };

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            m7->vtable->set_value(m7, i, j, arr[i][j]);
        }
    }


    Matrix *orthorgonal = GramSchmidt(m7);

    m7->vtable->print(m7);
    printf("\n====================\n");
    orthorgonal->vtable->print(orthorgonal);
    printf("\n");
}

void matrix_test() {
    printf("Matrix Get Test \n");

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

void vector_test(){
    //test vector addtion
    printf("\n vector addtion\n");
    double *v1 = New_Vector(3);
    double *v2 = New_Vector(3);
    v1[0] = 1;
    v1[1] = 2;
    v1[2] = 3;

    v2[0] = 4;
    v2[1] = 5;
    v2[2] = 6;

    vector_add(v1, v2, 3, v1);

    print_vector(v1, 3, "v1");

    //test vector scalar multiply
    printf("\n vector scalar multiply\n");
    vector_scalar_multiply(v1, 2, 3, v1);
    print_vector(v1, 3,"v1");

    //test vector dot product
    printf("\n vector dot product\n");
    print_vector(v1, 3,"v1");
    print_vector(v2, 3,"v2");
    double res = vector_dot_product(v1, v2, 3);
    printf("v1 dot v2 = %f\n", res); 

    //test vector norm
    printf("\n vector norm\n");
    print_vector(v1, 3,"v1");
    double norm = vector_norm(v1, 3);
    printf("norm = %f\n", norm);

    //test projection
    printf("\n vector projection\n");

    v1[0] = 0;
    v1[1] = 2;
    v1[2] = 0;

    v2[0] = 0;
    v2[1] = 2;
    v2[2] = 2;


    print_vector(v1, 3,"v1");
    print_vector(v2, 3,"v2");
    double *v3 = New_Vector(3);
    projection(v1, v2, 3, v3);
    print_vector(v3, 3,"v3");


}

void matrix_multiply_test(){
    printf("\nProblem 2 ProductMatrix\n");
    Matrix *b = New_Matrix_row_col(3, 3);
    // init b to identity matrix
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == j)
            {
                b->vtable->set_value(b, i, j, 2);
            }
        }
    }

    Matrix *c = New_Matrix_row_col(3, 4);
    double values[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            c->vtable->set_value(c, i, j, values[i][j]);
        }
    }
    // print a b and c with print function
    printf("\n a \n");
    Matrix *a = New_Matrix_row_col(3, 4);
    b->vtable->matrix_multiply(b, c, a);
    a->vtable->print(a);
    printf("\n b \n");
    b->vtable->print(b);
    printf("\n c \n");
    c->vtable->print(c);

    Matrix_destroy(a);
    Matrix_destroy(b);
    Matrix_destroy(c);
}