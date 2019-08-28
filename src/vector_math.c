#include <math.h>

/**
 * Calculates absolute value of vector
 */
double
abs_vector(double *vector, int vecLen)
{
    double absVal = 0;

    for (int i = 0; i < vecLen; i++){
        absVal = absVal + fabs(vector[i]);
    }

    return sqrt(absVal);
}


/**
 * Calculates the inverse of a matrix
 * The matrix needs to be diagonal i.e. a vector
 */
int
inv_matrix(double *vector, int vecLen)
{
    for (int i = 0; i < vecLen; i++)
    {
        vector[i] = 1/vector[i];
    }
    
    return 0;
}


/**
 * Calculates the subtraction between two vectors
 */
int
sub_vector(double *vec1, double *vec2, int vecLen, double *result)
{
    for (int i = 0; i < vecLen; i++)
    {
        result[i] = vec1[i] - vec2[i];
    }
    return 0;
}


/**
 * Calculates the dot product from two vectors
 */
double
dot_product(double *vec1, double *vec2, int vecLen)
{
    double result = 0;
    for (int i = 0; i < vecLen; i++)
    {
        result = result + vec1[i]*vec2[i];
    }
    return result;
}


/**
 * Calculates the cross product of two vectors
 */
int
element_product(double *vec1, double *vec2, int vecLen, double *result)
{
    for (int i = 0; i < vecLen; i++)
    {
        result[i] = vec1[i]*vec2[i];
    }
    return 0;
}