#' Automatically run every time-series feature calculation included in the catchaMouse16 set.
#' @param data a numerical time-series input vector
#' @return object of class DataFrame that contains the summary statistics for each feature
#' @author Trent Henderson
#' @export
#' @examples
#' timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)
#' outs <- catchaMouse16_all(timeseries)
#'

catchaMouse16_all <- function(data){

names <- c('SY_SlidingWindow',
           'SY_DriftingMean50_min',
           'CO_AddNoise_1_even_10_ami_at_10',
           'AC_nl_036',
           'AC_nl_035',
           'AC_nl_112',
           'IN_AutoMutualInfoStats_diff_20_gaussian_ami8',
           'CO_HistogramAMI_even_10_3',
           'CO_HistogramAMI_even_2_3',
           'CO_TranslateShape_circle_35_pts_statav4_m',
           'CO_TranslateShape_circle_35_pts_std',
           'DN_RemovePoints_absclose_05_ac2rat',
           'FC_LoopLocalSimple_mean_stderr_chn',
           'PH_Walker_momentum_5_w_momentumzcross',
           'PH_Walker_biasprop_05_01_sw_meanabsdiff',
           'ST_LocalExtrema_n100_diffmaxabsmin');

values = c();

for (feature in names){
    fh = get(feature);
    values = append(values, fh(data));
}

outData = data.frame(names = names, values = values);

return(outData)

}
