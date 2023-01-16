#include "matrix.h"

Matrix *MatSym(size_t n)
{
    Matrix* res = New_Matrix(n,n);
        


    return res;
}
Matrix *MatReg(size_t n){return NULL;};
Matrix *MatRegI(size_t n){return NULL;};
Matrix *MatRegU(size_t n){return NULL;};
Matrix *MatRand(size_t n, size_t m, double p){return NULL;};

// problem 2
Matrix *ProductMatrix(Matrix *B, Matrix *c){return NULL;};
double Trans(Matrix *A){return 0.0;}

Matrix *GramSchmidt(Matrix *A){return NULL;};