#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_poly.h>
#include <aSubRecord.h>

/* Polynomial fitting
 *
 * Inputs:
 * INPA: X Array
 * INPB: Len of X Array
 * INPC: Y Array
 * INPD: Len of Y Array
 * INPE: Degree (n)
 *
 * Outputs:
 * OUTA: Array of coefficents
 * OUTB: The sum of squares of the residuals from the best-fit
 * */
static long polynomial_fit(aSubRecord *psr) {
    long order, n, len_x, len_y;
    int i, j;
    double * data_x, * data_y;
    double chisq;

    data_x = (double *) psr->a;
    data_y = (double *) psr->c;

    len_x = *((long*) psr->b);
    len_y = *((long*) psr->d);

    order = *((long*) psr->e);


    //printf("len_x %d neva %d \n", len_x, psr->nea);

    //printf("leny %d order %d nova %d \n", len_y, order, psr->nova);
    //Invalid inputs
    if (len_x != len_y || len_x <= 1 || len_x < order || psr->novu < order) {
        return 1;
    }
    n = len_x;

//    double* array_out = (double*)psr->vala;
    double *array_out[] = {(double*)psr->vala,(double*)psr->valb, (double*)psr->valc, (double*)psr->vald, (double*)psr->vale, (double*)psr->valf, (double*)psr->valg, (double*)psr->valh, (double*)psr->vali, (double*)psr->valj, (double*)psr->valk};
    double* array_out2 = (double*)psr->valu;

    gsl_vector *y, *c;
    gsl_matrix *X, *cov;
    y = gsl_vector_alloc (n);
    c = gsl_vector_alloc (order+1);
    X   = gsl_matrix_alloc (n, order+1);
    cov = gsl_matrix_alloc (order+1, order+1);

    i = 0;
    for (i = 0; i < n; i++) {
        j = 0;
        for (j = 0; j < order+1; j++) {  
          gsl_matrix_set (X, i, j, pow(data_x[i],j));
        }
        gsl_vector_set (y, i, data_y[i]);
    }

    gsl_multifit_linear_workspace * work = gsl_multifit_linear_alloc (n, order+1);
    gsl_multifit_linear (X, y, c, cov, &chisq, work);
    gsl_multifit_linear_free (work);

    //i = 0 is the last coefficient
    // get the coefficents
    for (i = 0; i < order+1; i++) {
        *(array_out[i]) = gsl_vector_get(c,i);
        array_out2[i] = gsl_vector_get(c,i);
    }

    //0 the not used coefficients
    for (i = order+1; i < 10; i++) {
        *(array_out[i]) = 0;
    }

    psr->nevu = order+1;

//    *((double*)psr->valb) = chisq;

    gsl_vector_free (y);
    gsl_vector_free (c);
    gsl_matrix_free (X);
    gsl_matrix_free (cov);

    return 0;
}


/* Replace negative values by 0
 *
 * Inputs:
 * INPA: Array
 * INPB: Len of Array
 *
 * Outputs:
 * OUTA: Array without negative values
 * */
static long remove_negatives(aSubRecord *psr) {
    long len;
    int i;
    double * data;

    data = (double *) psr->a;

    len = *((long*) psr->b);

    if (psr->nova < len) {
        return 1;
    }


    double* array_out = (double*)psr->vala;

    for (i = 0; i < len; i++) {
        if (data[i] < 0)
            array_out[i] = 0;
        else
            array_out[i] = data[i];
    }

    psr->neva = len;

    return 0;
}


/* Fitted curve
 *
 * Inputs:
 * INPA: Coefficients array
 * INPB: Order
 * INPC: X Array (to be evalued)
 * INPD: Len of X Array
 *
 * Outputs:
 * OUTA: Fitted curve
 * */
static long fitted_curve(aSubRecord *psr) {
    long order, len_x;
    int i;
    double * data_x, * coef;

    coef = (double *) psr->a;
    data_x = (double *) psr->c;

    order = *((long*) psr->b);
    len_x    = *((long*) psr->d);

    double* array_out = (double*)psr->vala;

    for (i = 0 ; i < len_x ; i ++){
        array_out[i] = gsl_poly_eval(coef, order, data_x[i]);
    }

    psr->neva = len_x;
    return 0;
}


// Register the functions for access by EPICS
#include <registryFunction.h>
#include <epicsExport.h>

epicsRegisterFunction(polynomial_fit);
epicsRegisterFunction(fitted_curve);
epicsRegisterFunction(remove_negatives);

