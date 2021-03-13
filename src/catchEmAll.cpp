// [[Rcpp::depends(RcppGSL)]]
#include <Rcpp.h>
#include <RcppGSL.h>

// include functions
extern "C" {
#include "CO_AutoCorr.h"
#include "DN_HistogramMode_10.h"
#include "DN_HistogramMode_5.h"
#include "DN_OutlierInclude.h"
#include "FC_LocalSimple.h"
#include "IN_AutoMutualInfoStats.h"
#include "MD_hrv.h"
#include "PD_PeriodicityWang.h"
#include "SB_BinaryStats.h"
#include "SB_CoarseGrain.h"
#include "SB_MotifThree.h"
#include "SB_TransitionMatrix.h"
#include "SC_FluctAnal.h"
#include "SP_Summaries.h"
#include "butterworth.h"
#include "fft.h"
#include "helper_functions.h"
#include "histcounts.h"
#include "splinefit.h"
#include "stats.h"
#include "SY_DriftingMean50_min.h"
#include "DN_RemovePoints_absclose_05_ac2rat.h"
//#include "AC_nl_036.h"
//#include "AC_nl_112.h"
#include "ST_LocalExtrema_n100_diffmaxabsmin.h"
#include "CO_TranslateShape.h"
#include "SC_FluctAnal_2_dfa_50_2_logi_r2_se2.h"
#include "IN_AutoMutualInfoStats_diff_20_gaussian_ami8.h"
#include "PH_Walker.h"
#include "FC_LoopLocalSimple_mean_stderr_chn.h"
#include "CO_HistogramAMI.h"
//#include "AC_nl_035.h"
#include "CO_AddNoise_1_even_10_ami_at_10.h"
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

// roxygen2 documentation code added by Trent Henderson, 11 March 2021

/*
double CO_Embed2_Basic_tau_incircle_1_C(double * in, int n)
{
  return CO_Embed2_Basic_tau_incircle(in, n, 1, -1);
}
// [[Rcpp::export]]
NumericVector CO_Embed2_Basic_tau_incircle_1(NumericVector x) {

  return R_wrapper(x, &CO_Embed2_Basic_tau_incircle_1_C, 0);

};
*/

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_HistogramMode_5(x)
//'
// [[Rcpp::export]]
NumericVector DN_HistogramMode_5(NumericVector x)
{
  return R_wrapper_double(x, &DN_HistogramMode_5, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_HistogramMode_10(x)
//'
// [[Rcpp::export]]
NumericVector DN_HistogramMode_10(NumericVector x)
{
  return R_wrapper_double(x, &DN_HistogramMode_10, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_f1ecac(x)
//'
// [[Rcpp::export]]
NumericVector CO_f1ecac(NumericVector x)
{
  return R_wrapper_int(x, &CO_f1ecac, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_FirstMin_ac(x)
//'
// [[Rcpp::export]]
NumericVector CO_FirstMin_ac(NumericVector x)
{
  return R_wrapper_int(x, &CO_FirstMin_ac, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_HistogramAMI_even_2_5(x)
//'
// [[Rcpp::export]]
NumericVector CO_HistogramAMI_even_2_5(NumericVector x)
{
  return R_wrapper_double(x, &CO_HistogramAMI_even_2_5, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_trev_1_num(x)
//'
// [[Rcpp::export]]
NumericVector CO_trev_1_num(NumericVector x)
{
  return R_wrapper_double(x, &CO_trev_1_num, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- MD_hrv_classic_pnn40(x)
//'
// [[Rcpp::export]]
NumericVector MD_hrv_classic_pnn40(NumericVector x)
{
  return R_wrapper_double(x, &MD_hrv_classic_pnn40, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SB_BinaryStats_mean_longstretch1(x)
//'
// [[Rcpp::export]]
NumericVector SB_BinaryStats_mean_longstretch1(NumericVector x)
{
  return R_wrapper_double(x, &SB_BinaryStats_mean_longstretch1, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SB_TransitionMatrix_3ac_sumdiagcov(x)
//'
// [[Rcpp::export]]
NumericVector SB_TransitionMatrix_3ac_sumdiagcov(NumericVector x)
{
  return R_wrapper_double(x, &SB_TransitionMatrix_3ac_sumdiagcov, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- PD_PeriodicityWang_th0_01(x)
//'
// [[Rcpp::export]]
NumericVector PD_PeriodicityWang_th0_01(NumericVector x)
{
  return R_wrapper_int(x, &PD_PeriodicityWang_th0_01, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_Embed2_Dist_tau_d_expfit_meandiff(x)
//'
// [[Rcpp::export]]
NumericVector CO_Embed2_Dist_tau_d_expfit_meandiff(NumericVector x)
{
  return R_wrapper_double(x, &CO_Embed2_Dist_tau_d_expfit_meandiff, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- IN_AutoMutualInfoStats_40_gaussian_fmmi(x)
//'
// [[Rcpp::export]]
NumericVector IN_AutoMutualInfoStats_40_gaussian_fmmi(NumericVector x)
{
  return R_wrapper_double(x, &IN_AutoMutualInfoStats_40_gaussian_fmmi, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- FC_LocalSimple_mean1_tauresrat(x)
//'
// [[Rcpp::export]]
NumericVector FC_LocalSimple_mean1_tauresrat(NumericVector x)
{
  return R_wrapper_double(x, &FC_LocalSimple_mean1_tauresrat, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_OutlierInclude_p_001_mdrmd(x)
//'
// [[Rcpp::export]]
NumericVector DN_OutlierInclude_p_001_mdrmd(NumericVector x)
{
  return R_wrapper_double(x, &DN_OutlierInclude_p_001_mdrmd, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_OutlierInclude_n_001_mdrmd(x)
//'
// [[Rcpp::export]]
NumericVector DN_OutlierInclude_n_001_mdrmd(NumericVector x)
{
  return R_wrapper_double(x, &DN_OutlierInclude_n_001_mdrmd, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SP_Summaries_welch_rect_area_5_1(x)
//'
// [[Rcpp::export]]
NumericVector SP_Summaries_welch_rect_area_5_1(NumericVector x)
{
  return R_wrapper_double(x, &SP_Summaries_welch_rect_area_5_1, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SB_BinaryStats_diff_longstretch0(x)
//'
// [[Rcpp::export]]
NumericVector SB_BinaryStats_diff_longstretch0(NumericVector x)
{
  return R_wrapper_double(x, &SB_BinaryStats_diff_longstretch0, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SB_MotifThree_quantile_hh(x)
//'
// [[Rcpp::export]]
NumericVector SB_MotifThree_quantile_hh(NumericVector x)
{
  return R_wrapper_double(x, &SB_MotifThree_quantile_hh, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1(x)
//'
// [[Rcpp::export]]
NumericVector SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1(NumericVector x)
{
  return R_wrapper_double(x, &SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1(x)
//'
// [[Rcpp::export]]
NumericVector SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1(NumericVector x)
{
  return R_wrapper_double(x, &SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SP_Summaries_welch_rect_centroid(x)
//'
// [[Rcpp::export]]
NumericVector SP_Summaries_welch_rect_centroid(NumericVector x)
{
  return R_wrapper_double(x, &SP_Summaries_welch_rect_centroid, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Carl H. Lubba
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- FC_LocalSimple_mean3_stderr(x)
//'
// [[Rcpp::export]]
NumericVector FC_LocalSimple_mean3_stderr(NumericVector x)
{
  return R_wrapper_double(x, &FC_LocalSimple_mean3_stderr, 1);
}

// ----------------------- catchaMouse16 ---------------------------

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SY_DriftingMean50_min(x)
//'
// [[Rcpp::export]]
NumericVector SY_DriftingMean50_min(NumericVector x)
{
  return R_wrapper_double(x, &SY_DriftingMean50_min, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- DN_RemovePoints_absclose_05_ac2rat(x)
//'
// [[Rcpp::export]]
NumericVector DN_RemovePoints_absclose_05_ac2rat(NumericVector x)
{
  return R_wrapper_double(x, &DN_RemovePoints_absclose_05_ac2rat, 1);
}



// NOTE: AC_nl_036 TO GO HERE ONCE C CODE IS FOUND

// NOTE: AC_nl_112 TO GO HERE ONCE C CODE IS FOUND



//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- ST_LocalExtrema_n100_diffmaxabsmin(x)
//'
// [[Rcpp::export]]
NumericVector ST_LocalExtrema_n100_diffmaxabsmin(NumericVector x)
{
  return R_wrapper_double(x, &ST_LocalExtrema_n100_diffmaxabsmin, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_TranslateShape_circle_35_pts_statav4_m(x)
//'
// [[Rcpp::export]]
NumericVector CO_TranslateShape_circle_35_pts_statav4_m(NumericVector x)
{
  return R_wrapper_double(x, &CO_TranslateShape_circle_35_pts_statav4_m, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_TranslateShape_circle_35_pts_std(x)
//'
// [[Rcpp::export]]
NumericVector CO_TranslateShape_circle_35_pts_std(NumericVector x)
{
  return R_wrapper_double(x, &CO_TranslateShape_circle_35_pts_std, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- SC_FluctAnal_2_dfa_50_2_logi_r2_se2(x)
//'
// [[Rcpp::export]]
NumericVector SC_FluctAnal_2_dfa_50_2_logi_r2_se2(NumericVector x)
{
  return R_wrapper_double(x, &SC_FluctAnal_2_dfa_50_2_logi_r2_se2, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- IN_AutoMutualInfoStats_diff_20_gaussian_ami8(x)
//'
// [[Rcpp::export]]
NumericVector IN_AutoMutualInfoStats_diff_20_gaussian_ami8(NumericVector x)
{
  return R_wrapper_double(x, &IN_AutoMutualInfoStats_diff_20_gaussian_ami8, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- PH_Walker_momentum_5_w_momentumzcross(x)
//'
// [[Rcpp::export]]
NumericVector PH_Walker_momentum_5_w_momentumzcross(NumericVector x)
{
  return R_wrapper_double(x, &PH_Walker_momentum_5_w_momentumzcross, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- PH_Walker_biasprop_05_01_sw_meanabsdiff(x)
//'
// [[Rcpp::export]]
NumericVector PH_Walker_biasprop_05_01_sw_meanabsdiff(NumericVector x)
{
  return R_wrapper_double(x, &PH_Walker_biasprop_05_01_sw_meanabsdiff, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- FC_LoopLocalSimple_mean_stderr_chn(x)
//'
// [[Rcpp::export]]
NumericVector FC_LoopLocalSimple_mean_stderr_chn(NumericVector x)
{
  return R_wrapper_double(x, &FC_LoopLocalSimple_mean_stderr_chn, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_HistogramAMI_even_10_3(x)
//'
// [[Rcpp::export]]
NumericVector CO_HistogramAMI_even_10_3(NumericVector x)
{
  return R_wrapper_double(x, &CO_HistogramAMI_even_10_3, 1);
}

//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_HistogramAMI_even_2_3(x)
//'
// [[Rcpp::export]]
NumericVector CO_HistogramAMI_even_2_3(NumericVector x)
{
  return R_wrapper_double(x, &CO_HistogramAMI_even_2_3, 1);
}



// NOTE: AC_nl_035 TO GO HERE ONCE C CODE IS FOUND



//' @param x a numerical time-series input vector
//' @return scalar value that denotes the calculated time-series statistic
//' @author Imran Alam
//' @export
//' @examples
//' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
//' outs <- CO_AddNoise_1_even_10_ami_at_10(x)
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
