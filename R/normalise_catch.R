#' Scale each value into sigmoidal range for visualisation and analysis.
#' @param x a vector of scalar values
#' @param method a rescaling/normalising method to apply
#' @return a vector of scalar values normalised into the selected range
#' @author Trent Henderson
#' @export
#' @examples
#' data <- 1 + 0.5 * 1:1000 + arima.sim(list(ma = 0.5), n = 1000)
#' outs <- normalise_catch(data, method = "MinMax")
#'

normalise_catch <- function(x, method = c("z-score", "Sigmoid", "RobustSigmoid", "MinMax")){

  method <- match.arg(method)

  #--------- Error catches ---------

  # Input vector

  if(!is.numeric(x)){
    stop("x should be a vector of numeric values.")
  }

  if(length(x) < 5){
    stop("length of x is too short to make reliable calculations.")
  }

  # Method selection

  the_methods <- c("z-score", "Sigmoid", "RobustSigmoid", "MinMax")
  '%ni%' <- Negate('%in%')

  if(method %ni% the_methods){
    stop("method should be a single selection of 'z-score', 'Sigmoid', 'RobustSigmoid' or 'MinMax'")
  }

  if(length(method) > 1){
    stop("method should be a single selection of 'z-score', 'Sigmoid', 'RobustSigmoid' or 'MinMax'")
  }

  #--------- Apply scaling ---------

  if(method == "z-score"){
    x_norm <- zscore_scaler(x)
  }

  if(method == "Sigmoid"){
    x_norm <- sigmoid_scaler(x)
  }

  if(method == "RobustSigmoid"){
    x_norm <- robustsigmoid_scaler(x)
  }

  if(method == "MinMax"){
    x_norm <- minmax_scaler(x)
  }

  return(x_norm)
}
