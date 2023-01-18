#ifndef F7DED081_6C7A_4C4E_BC45_79E42C8E1623
#define F7DED081_6C7A_4C4E_BC45_79E42C8E1623
#include "matrix.h"
// problem 1
extern Matrix* MatSym(size_t n);
extern Matrix* MatReg(size_t n);
extern Matrix* MatRegI(size_t n);
extern Matrix* MatRegU(size_t n);
extern Matrix* MatRand(size_t n,size_t m,double p);

//problem 2
extern Matrix* ProductMatrix(Matrix* B,Matrix* c);
extern double Trans(Matrix* A);

extern void Problem_1();
extern void Problem_2();
extern Matrix* GramSchmidt(Matrix* A);
extern void Problem_3();
extern void Problem_3_3By3();

#endif /* F7DED081_6C7A_4C4E_BC45_79E42C8E1623 */
