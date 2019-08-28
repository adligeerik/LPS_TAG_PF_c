#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

double abs_vector(double *vector, int vecLen);
int sub_vector(double *vec1, double *vec2, int vecLen, double *result);
double dot_product(double *vec1, double *vec2, int vecLen);
int element_product(double *vec1, double *vec2, int vecLen, double *result);
double inv_matrix(double *vector, int vecLen, double *result);

#endif