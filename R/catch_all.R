#' Automatically run every time-series feature calculation included in both catch22 and catchaMouse16 sets.
#' @param data a numerical time-series input vector
#' @return object of class DataFrame that contains the summary statistics for each feature
#' @author Trent Henderson
#' @examples
#' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
#' outs <- catch_all(timeseries)
#' @export
#'

catch_all <- function(data){

  names <- c('DN_HistogramMode_5',
             'DN_HistogramMode_10',
             'CO_f1ecac',
             'CO_FirstMin_ac',
             'CO_HistogramAMI_even_2_5',
             'CO_trev_1_num',
             'MD_hrv_classic_pnn40',
             'SB_BinaryStats_mean_longstretch1',
             'SB_TransitionMatrix_3ac_sumdiagcov',
             'PD_PeriodicityWang_th0_01',
             'CO_Embed2_Dist_tau_d_expfit_meandiff',
             'IN_AutoMutualInfoStats_40_gaussian_fmmi',
             'FC_LocalSimple_mean1_tauresrat',
             'DN_OutlierInclude_p_001_mdrmd',
             'DN_OutlierInclude_n_001_mdrmd',
             'SP_Summaries_welch_rect_area_5_1',
             'SB_BinaryStats_diff_longstretch0',
             'SB_MotifThree_quantile_hh',
             'SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1',
             'SC_FluctAnal_2_dfa_50_1_2_logi_prop_r1',
             'SP_Summaries_welch_rect_centroid',
             'FC_LocalSimple_mean3_stderr',
             'SY_DriftingMean50_min',
             'DN_RemovePoints_absclose_05_ac2rat',
             'AC_nl_036',
             'AC_nl_112',
             'ST_LocalExtrema_n100_diffmaxabsmin',
             'CO_TranslateShape_circle_35_pts_statav4_m',
             'CO_TranslateShape_circle_35_pts_std',
             'SC_FluctAnal_2_dfa_50_2_logi_r2_se2',
             'IN_AutoMutualInfoStats_diff_20_gaussian_ami8',
             'PH_Walker_momentum_5_w_momentumzcross',
             'PH_Walker_biasprop_05_01_sw_meanabsdiff',
             'FC_LoopLocalSimple_mean_stderr_chn',
             'CO_HistogramAMI_even_10_3',
             'CO_HistogramAMI_even_2_3',
             'AC_nl_035',
             'CO_AddNoise_1_even_10_ami_at_10');

  values = c();

  for (feature in names){
    fh = get(feature);
    values = append(values, fh(data));
  }

  outData = data.frame(names = names, values = values);

  return(outData)

}
