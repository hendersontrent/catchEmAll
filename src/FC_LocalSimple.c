#include <math.h>
#include <string.h>
#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "CO_AutoCorr.h"
#include "FC_LocalSimple.h"

static void abs_diff(const double a[], const int size, double b[])
{
    for (int i = 1; i < size; i++) {
        b[i - 1] = fabs(a[i] - a[i - 1]);
    }
}

double fc_local_simple(const double y[], const int size, const int train_length)
{
    double * y1 = malloc((size - 1) * sizeof *y1);
    abs_diff(y, size, y1);
    double m = mean(y1, size - 1);
    free(y1);
    return m;
}

double FC_LocalSimple_mean_tauresrat(const double y[], const int size, const int train_length)
{

    // NaN check
    for(int i = 0; i < size; i++)
    {
        if(isnan(y[i]))
        {
            return NAN;
        }
    }

    double * res = malloc((size - train_length) * sizeof *res);

    for (int i = 0; i < size - train_length; i++)
    {
        double yest = 0;
        for (int j = 0; j < train_length; j++)
        {
            yest += y[i+j];

        }
        yest /= train_length;

        res[i] = y[i+train_length] - yest;
    }

    double resAC1stZ = co_firstzero(res, size - train_length, size - train_length);
    double yAC1stZ = co_firstzero(y, size, size);
    double output = resAC1stZ/yAC1stZ;

    free(res);
    return output;

}

double FC_LocalSimple_mean_stderr(const double y[], const int size, const int train_length)
{
    // NaN check
    for(int i = 0; i < size; i++)
    {
        if(isnan(y[i]))
        {
            return NAN;
        }
    }

    double * res = malloc((size - train_length) * sizeof *res);

    for (int i = 0; i < size - train_length; i++)
    {
        double yest = 0;
        for (int j = 0; j < train_length; j++)
        {
            yest += y[i+j];

        }
        yest /= train_length;

        res[i] = y[i+train_length] - yest;
    }

    double output = stddev(res, size - train_length);

    free(res);
    return output;

}

double FC_LocalSimple_mean3_stderr(const double y[], const int size)
{
    return FC_LocalSimple_mean_stderr(y, size, 3);
}

double FC_LocalSimple_mean1_tauresrat(const double y[], const int size){
    return FC_LocalSimple_mean_tauresrat(y, size, 1);
}

double FC_LocalSimple_mean_taures(const double y[], const int size, const int train_length)
{
    double * res = malloc((size - train_length) * sizeof *res);

    // first z-score
    // no, assume ts is z-scored!!
    //zscore_norm(y, size);

    for (int i = 0; i < size - train_length; i++)
    {
        double yest = 0;
        for (int j = 0; j < train_length; j++)
        {
            yest += y[i+j];

        }
        yest /= train_length;

        res[i] = y[i+train_length] - yest;
    }

    int output = co_firstzero(res, size - train_length, size - train_length);

    free(res);
    return output;

}

double FC_LocalSimple_lfit_taures(const double y[], const int size)
{
    // set tau from first AC zero crossing
    int train_length = co_firstzero(y, size, size);

    double * xReg = malloc(train_length * sizeof * xReg);
    // double * yReg = malloc(train_length * sizeof * yReg);
    for(int i = 1; i < train_length+1; i++)
    {
        xReg[i-1] = i;
    }

    double * res = malloc((size - train_length) * sizeof *res);

    double m = 0.0, b = 0.0;

    for (int i = 0; i < size - train_length; i++)
    {
        linreg(train_length, xReg, y+i, &m, &b);

        // fprintf(stdout, "i=%i, m=%f, b=%f\n", i, m, b);

        res[i] = y[i+train_length] - (m * (train_length+1) + b);
    }

    int output = co_firstzero(res, size - train_length, size - train_length);

    free(res);
    free(xReg);
    // free(yReg);

    return output;

}

double FC_LocalSimple_cam(const double y[], const int size, int trainLength) {

    // Method:- mean
    int i, j;
    int lp = trainLength;

    // range over which to evaluate
    int evalr_len = size - lp; //lp+1:N
    if (evalr_len == 0) {
        printf("FC_LocalSimple: Time Series too short for forecasting\n");
        return NAN;
    }
    int *evalr = (int*) malloc(evalr_len * sizeof(int));
    for (i = 0; i < evalr_len; i++)
        evalr[i] = i + lp + 1;

    double *res = (double*) malloc(evalr_len * sizeof(double));
    memset(res, 0, evalr_len * sizeof(double));
    for (i = 0; i < evalr_len; i++) {
        for (j = evalr[i] - lp - 1; j < evalr[i] - 1; j++)
            res[i] += y[j];
        res[i] = (res[i]/lp) - y[evalr[i] - 1];
    }

    double out = stddev(res, evalr_len);
    /*out[1] = SY_SlidingWindow(res, evalr_len, "std", "std", 5, 1); // sws
     out[2] = SY_SlidingWindow(res, evalr_len, "mean", "std", 5, 1); // swm
     int tau[1] = {1};
     out[3] = *CO_AutoCorr(res, evalr_len, tau, 1); // ac1
     tau[0] = 2;
     out[4] = *CO_AutoCorr(res, evalr_len, tau, 1); // ac2*/

    free(evalr);
    free(res);
    return out;
}

double FC_LoopLocalSimple_mean_stderr_chn(const double y[], const int size) {

    // Check NAN
    int i;
    for (i = 0; i < size; i++)
        if (isnan(y[i]))
            return NAN;

        int trainLengthRange = 10;
        double *stats_st = (double*) malloc(trainLengthRange * sizeof(double)); // 10 x 5 matrix
        double mi = INT_MAX, ma = -INT_MAX;
        for (i = 0; i < trainLengthRange; i++) {
            stats_st[i] = FC_LocalSimple_cam(y, size, i+1);
            if (mi > stats_st[i])   mi = stats_st[i];
            if (ma < stats_st[i])   ma = stats_st[i];
        }
        double range = ma - mi;

        double *st_diff = (double*) malloc((trainLengthRange - 1) * sizeof(double));
        diff(stats_st, trainLengthRange, st_diff);
        double stderr_chn = mean(st_diff, trainLengthRange - 1)/ range;

        free(stats_st);
        free(st_diff);

        return stderr_chn;
}
