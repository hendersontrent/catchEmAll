#include <Rcpp.h>

// include functions
extern "C" {
#include "SY_DriftingMean50_min.h"
#include "DN_RemovePoints_absclose_05_ac2rat.h"
#include "AC_nl_036.h"
#include "AC_nl_112.h"
#include "ST_LocalExtrema_n100_diffmaxabsmin.h"
#include "CO_TranslateShape_circle_35_pts_statav4_m.h"
#include "CO_TranslateShape_circle_35_pts_std.h"
#include "SC_FluctAnal_2_dfa_50_2_logi_r2_se2.h"
#include "IN_AutoMutualInfoStats_diff_20_gaussian_ami8.h"
#include "PH_Walker_momentum_5_w_momentumzcross.h"
#include "PH_Walker_biasprop_05_01_sw_meanabsdiff.h"
#include "FC_LoopLocalSimple_mean_stderr_chn.h"
#include "CO_HistogramAMI_even_10_3.h"
#include "CO_HistogramAMI_even_2_3.h"
#include "AC_nl_035.h"
#include "CO_AddNoise_1_even_10_ami_at_10.h"
#include "fft.h"
#include "helper_functions.h"
#include "histcounts.h"
#include "splinefit.h"
#include "stats.h"
}

using namespace Rcpp;

// Learn more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//


// universal wrapper for a function that takes a double array and its length
// and outputs a scalar double
NumericVector R_wrapper_double(NumericVector x, double (*f) (const double*, const int), int normalize) {

  int n = x.size();
  double * arrayC = new double[n];
  double out;

  int i;
  for (i=0; i<n; i++){
    arrayC[i] = x[i];
  }

  if (normalize){

    double * y_zscored = new double[n];

    zscore_norm2(arrayC, n, y_zscored);

    out = f(y_zscored, n);

    // free(y_zscored);
  }
  else {
    out = f(arrayC, n);
  }

  // free(arrayC);

  NumericVector outVec = NumericVector::create(out);

  return outVec;

};

// universal wrapper for a function that takes a double array and its length
// and outputs a scalar double
NumericVector R_wrapper_int(NumericVector x, int (*f) (const double*, const int), int normalize) {

  int n = x.size();
  double * arrayC = new double[n];
  int out;

  int i;
  for (i=0; i<n; i++){
    arrayC[i] = x[i];
  }

  if (normalize){

    double * y_zscored = new double[n];

    zscore_norm2(arrayC, n, y_zscored);

    out = f(y_zscored, n);

    // free(y_zscored);
  }
  else {
    out = f(arrayC, n);
  }

  // free(arrayC);

  NumericVector outVec = NumericVector::create(out);

  return outVec;

};

//-------------------------------------------------------------------------
//----------------------- Feature functions -------------------------------
//-------------------------------------------------------------------------

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SY_DriftingMean50_min(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector SY_DriftingMean50_min(NumericVector x)
{
  return R_wrapper_double(x, &SY_DriftingMean50_min, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_RemovePoints_absclose_05_ac2rat(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector DN_RemovePoints_absclose_05_ac2rat(NumericVector x)
{
  return R_wrapper_double(x, &DN_RemovePoints_absclose_05_ac2rat, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- AC_nl_036(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector AC_nl_036(NumericVector x)
{
  return R_wrapper_int(x, &AC_nl_036, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- AC_nl_112(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector AC_nl_112(NumericVector x)
{
  return R_wrapper_int(x, &AC_nl_112, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- ST_LocalExtrema_n100_diffmaxabsmin(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector ST_LocalExtrema_n100_diffmaxabsmin(NumericVector x)
{
  return R_wrapper_double(x, &ST_LocalExtrema_n100_diffmaxabsmin, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_TranslateShape_circle_35_pts_statav4_m(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector CO_TranslateShape_circle_35_pts_statav4_m(NumericVector x)
{
  return R_wrapper_double(x, &CO_TranslateShape_circle_35_pts_statav4_m, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_TranslateShape_circle_35_pts_std(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector CO_TranslateShape_circle_35_pts_std(NumericVector x)
{
  return R_wrapper_double(x, &CO_TranslateShape_circle_35_pts_std, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SC_FluctAnal_2_dfa_50_2_logi_r2_se2(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector SC_FluctAnal_2_dfa_50_2_logi_r2_se2(NumericVector x)
{
  return R_wrapper_double(x, &SC_FluctAnal_2_dfa_50_2_logi_r2_se2, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- IN_AutoMutualInfoStats_diff_20_gaussian_ami8(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector IN_AutoMutualInfoStats_diff_20_gaussian_ami8(NumericVector x)
{
  return R_wrapper_double(x, &IN_AutoMutualInfoStats_diff_20_gaussian_ami8, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- PH_Walker_momentum_5_w_momentumzcross(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector PH_Walker_momentum_5_w_momentumzcross(NumericVector x)
{
  return R_wrapper_int(x, &PH_Walker_momentum_5_w_momentumzcross, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- PH_Walker_biasprop_05_01_sw_meanabsdiff(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector PH_Walker_biasprop_05_01_sw_meanabsdiff(NumericVector x)
{
  return R_wrapper_double(x, &PH_Walker_biasprop_05_01_sw_meanabsdiff, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- FC_LoopLocalSimple_mean_stderr_chn(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector FC_LoopLocalSimple_mean_stderr_chn(NumericVector x)
{
  return R_wrapper_double(x, &FC_LoopLocalSimple_mean_stderr_chn, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_HistogramAMI_even_10_3(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector CO_HistogramAMI_even_10_3(NumericVector x)
{
  return R_wrapper_double(x, &CO_HistogramAMI_even_10_3, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_HistogramAMI_even_2_3(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector CO_HistogramAMI_even_2_3(NumericVector x)
{
  return R_wrapper_double(x, &CO_HistogramAMI_even_2_3, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- AC_nl_035(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector AC_nl_035(NumericVector x)
{
  return R_wrapper_double(x, &AC_nl_035, 1);
}

//' @param data a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_AddNoise_1_even_10_ami_at_10(timeseries)
//' @export
//'
// [[Rcpp::export]]
NumericVector CO_AddNoise_1_even_10_ami_at_10(NumericVector x)
{
  return R_wrapper_double(x, &CO_AddNoise_1_even_10_ami_at_10, 1);
}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//


/*** R
arraysum(c(42, 21));
*/
