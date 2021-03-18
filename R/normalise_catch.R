#' Scale each value into sigmoidal range for visualisation and analysis.
#' @param x a vector of scalar values
#' @return a vector of scalar values normalised into sigmoidal range [0,1]
#' @author Trent Henderson
#' @export
#' @examples
#' data <- seq(from = 1, to = 1000, by = 1)
#' outs <- normalise_catch(data)
#'

normalise_catch <- function(x){

  if(!is.numeric(x)){
    stop("x should be a vector of numeric values.")
  }

  x_norm <- norm_scaler(x)

  return(x_norm)
}
