#include <math.h>
#include <stdlib.h>
//#include <stdio.h>

/**
 * Calculates absolute value of vector
 */
double
abs_vector(double *vector, int vecLen)
{
    double absVal = 1;

    for (int i = 0; i < vecLen; i++)
    {
        absVal = absVal * vector[i];
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
        result[i] = 1 / vector[i];
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
        result = result + vec1[i] * vec2[i];
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
        result[i] = vec1[i] * vec2[i];
        //printf("vec1 %f\n",vec1[i]);
        //printf("vec2 %f\n",vec2[i]);
        //printf("elem %f\n",result[i]);
    }
    return 0;
}

/**
 * Gives a number from a gaussian distrubution with mean and variance
 */
double
gauss(double mu, double sigma)
{
    double U1, U2, W, mult;
    static double X1, X2;
    static int call = 0;

    if (call == 1)
    {
        call = !call;
        return (mu + sigma * (double)X2);
    }

    do
    {
        U1 = -1 + ((double)rand() / RAND_MAX) * 2;
        U2 = -1 + ((double)rand() / RAND_MAX) * 2;
        W = pow(U1, 2) + pow(U2, 2);
    } while (W >= 1 || W == 0);

    mult = sqrt((-2 * log(W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;
    //printf("h3j\n");
    return (mu + sigma * (double)X1);
}