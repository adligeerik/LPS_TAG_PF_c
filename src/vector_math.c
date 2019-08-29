#include <math.h>
//#include <stdio.h>

/**
 * Calculates absolute value of vector
 */
double
abs_vector(double *vector, int vecLen)
{
    double absVal = 1;

    for (int i = 0; i < vecLen; i++){
        absVal = absVal*vector[i];
    }
    //printf("absval :%f\n",absVal);

    return absVal;
}


/**
 * Calculates the inverse of a matrix
 * The matrix needs to be diagonal i.e. a vector
 */
int
inv_matrix(double *vector, int vecLen, double *result)
{
    for (int i = 0; i < vecLen; i++)
    {
        result[i] = 1/vector[i];
        //printf("inv %f\n",result[i]);
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
        //printf("sub %f\n",result[i]);
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
    //printf("dot %f\n",result);
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
        //printf("vec1 %f\n",vec1[i]);
        //printf("vec2 %f\n",vec2[i]);
        //printf("elem %f\n",result[i]);
    }
    return 0;
}

/**
 * Gives a number between min and max with a normal distrubution
 */
double 
gauss(double min, double max)
{
    double result;
    return result;
}