#' Produce a principal components analysis (PCA) on normalised feature values and render a scatterplot
#' @import dplyr
#' @import ggplot2
#' @import tibble
#' @importFrom magrittr %>%
#' @importFrom tidyr drop_na
#' @importFrom broom augment
#' @param data a dataframe with at least 2 columns called 'names' and 'values'
#' @param is_normalised a Boolean as to whether the input feature values have already been scaled. Defaults to FALSE
#' @param id_var a string specifying the ID variable to group data on (if one exists). Defaults to NULL
#' @param method a rescaling/normalising method to apply. Defaults to 'RobustSigmoid'
#' @param plot a Boolean as to whether a bivariate plot should be returned or the calculation dataframe. Defaults to TRUE
#' @return if plot = TRUE, returns an object of class ggplot, if plot = FALSE returns an object of class dataframe with PCA results
#' @author Trent Henderson
#' @seealso [catchEmAll::normalise_catch()]
#' @export
#' @examples
#' \dontrun{
#' data1 <- 1 + 0.5 * 1:1000 + arima.sim(list(ma = 0.5), n = 1000)
#' data2 <- rnorm(1000, mean = 0, sd = 1)
#' outs1 <- catch22_all(data1)
#' outs1['group'] <- 'Group 1'
#' outs2 <- catch22_all(data2)
#' outs2['group'] <- 'Group 2'
#' outs <- rbind(outs1, outs2)
#' plot_low_dimension(outs, is_normalised = FALSE, id_var = "group", method = "RobustSigmoid", plot = TRUE)
#' }
#'

plot_low_dimension(outs, is_normalised = FALSE, id_var = "group", method = "RobustSigmoid", plot = TRUE){

  # Make RobustSigmoid the default

  if(missing(method)){
    method <- "RobustSigmoid"
  } else{
    method <- match.arg(method)
  }

  expected_cols_1 <- "names"
  expected_cols_2 <- "values"
  the_cols <- colnames(data)
  '%ni%' <- Negate('%in%')

  if(expected_cols_1 %ni% the_cols){
    stop("data should contain at least two columns called 'names' and 'values'. These are automatically produced by feature calculations such as catch_all(). Please consider running one of these first and then passing the resultant dataframe in to this function.")
  }

  if(expected_cols_2 %ni% the_cols){
    stop("data should contain at least two columns called 'names' and 'values'. These are automatically produced by feature calculations such as catch_all(). Please consider running one of these first and then passing the resultant dataframe in to this function.")
  }

  if(!is.numeric(data$values)){
    stop("'values' column in data should be a numerical vector.")
  }

  if(!is.null(id_var) & !is.character(id_var)){
    stop("id_var should be a string specifying a variable in the input data that uniquely identifies each observation.")
  }

  # Method selection

  the_methods <- c("z-score", "Sigmoid", "RobustSigmoid", "MinMax", "MeanSubtract")

  if(method %ni% the_methods){
    stop("method should be a single selection of 'z-score', 'Sigmoid', 'RobustSigmoid', 'MinMax' or 'MeanSubtract'")
  }

  if(length(method) > 1){
    stop("method should be a single selection of 'z-score', 'Sigmoid', 'RobustSigmoid', 'MinMax' or 'MeanSubtract'")
  }

  #------------- Assign ID variable ---------------

  if(is.null(id_var)){
    data_id <- data %>%
      dplyr::mutate(id = dplyr::row_number())
  } else{
    data_id <- data %>%
      dplyr::rename(id = dplyr::all_of(id_var))
  }

  #------------- Normalise data -------------------

  if(is_normalised){
    normed1 <- data_id
  } else{
    normed <- data_id %>%
      dplyr::filter(!is.nan(values)) %>%
      dplyr::select(c(id, names, values)) %>%
      dplyr::group_by(names) %>%
      dplyr::mutate(values = normalise_catch(values, method = method)) %>%
      dplyr::ungroup() %>%
      tidyr::drop_na()

    if(nrow(normed) != nrow(data_id)){
      message("Filtered out rows containing NaNs.")
    }
  }

  #------------- Perform PCA ----------------------

  # Produce matrix

  dat <- normed %>%
    tidyr::pivot_wider(id_cols = id, names_from = names, values_from = values) %>%
    tibble::column_to_rownames(var = "id")

  # PCA calculation

  pca_fit <- dat %>%
    prcomp(scale = FALSE)

  #------------- Output & graphic -----------------

  if(plot){

    p <- pca_fit %>%
      broom::augment(dat) %>%
      ggplot2::ggplot(ggplot2::aes(x = .fittedPC1, y = .fittedPC2)) +
      ggplot2::geom_point(size = 1.5, colour = "black") +
      ggplot2::labs(title = "Low-dimension representation of each time-series' feature vectors",
                    x = "PC 1",
                    y = "PC2") +
      ggplot2::theme_bw() +
      ggplot2::theme(panel.grid.minor = ggplot2::element_blank())

    return(p)
  } else{
    return(pca_fit)
  }
}
