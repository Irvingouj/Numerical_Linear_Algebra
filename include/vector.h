#ifndef DC6938C5_B495_4CFF_8AE6_45EE593E4DA3
#define DC6938C5_B495_4CFF_8AE6_45EE593E4DA3
#include "matrix.h"
#include <stdlib.h>

double** matrix_to_col(Matrix* A);
double** init_2d_array(size_t n, size_t m);
void free_double_pointer(double** A, size_t n);
void vector_add(double *a, double *b, size_t n, double *res);
void vector_subtract(double *a, double *b, size_t n, double *res);
void vector_scalar_multiply(double *a, double b, size_t n, double *res);
void vector_copy(double *a, size_t n, double *res);
double vector_norm(double *a, size_t n);
double vector_dot_product(double *a, double *b, size_t n);
void projection(double *u,double *v, size_t n, double *res);
void vector_normalize(double *u, size_t n);
extern double* New_Vector(size_t n);
void print_vector(double* v, size_t n,char *name);
#endif /* DC6938C5_B495_4CFF_8AE6_45EE593E4DA3 */
