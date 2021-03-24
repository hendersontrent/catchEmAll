#' Produce a principal components analysis (PCA) on normalised feature values and render a scatterplot
#' @import dplyr
#' @import ggplot2
#' @import tibble
#' @importFrom magrittr %>%
#' @importFrom tidyr drop_na
#' @importFrom broom augment
#' @importFrom broom tidy
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

plot_low_dimension <- function(data, is_normalised = FALSE, id_var = NULL, method = "RobustSigmoid", plot = TRUE){

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
    normed <- data_id
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

  # Check amount of NA in each feature vector to tell which ones to drop prior to PCA

  check_na_vector <- dat %>%
    tidyr::pivot_longer(everything(), names_to = "names", values_to = "values") %>%
    dplyr::mutate(category = ifelse(is.na(values), "N/A", "Not N/A")) %>%
    dplyr::group_by(names, category) %>%
    dplyr::summarise(counter = n()) %>%
    dplyr::ungroup() %>%
    dplyr::group_by(names) %>%
    dplyr::mutate(props = counter / sum(counter)) %>%
    dplyr::ungroup() %>%
    dplyr::filter(category == "Not N/A") %>%
    dplyr::filter(props >= 0.7)

  filtered_colnames <- unique(check_na_vector$names)

  dat_filtered <- dat %>%
    dplyr::select(c(all_of(filtered_colnames))) %>%
    tidyr::drop_na()

  if(ncol(dat_filtered) != ncol(dat)){
    message("Dropped feature vectors with >=30% NAs to enable PCA")
  }

  if(nrow(dat_filtered) != nrow(dat)){
    message("Dropped rows with NAs to enable PCA.")
  }

  # PCA calculation

  pca_fit <- dat_filtered %>%
    prcomp(scale = FALSE)

  # Retrieve eigenvalues and tidy up variance explained for plotting

  eigens <- pca_fit %>%
    broom::tidy(matrix = "eigenvalues") %>%
    dplyr::filter(PC %in% c(1,2)) %>% # Filter to just the 2 going on the plot
    dplyr::select(c(PC, percent)) %>%
    dplyr::mutate(percent = round(percent*100), digits = 1)

  eigen_pc1 <- eigens %>%
    dplyr::filter(PC == 1)

  eigen_pc2 <- eigens %>%
    dplyr::filter(PC == 2)

  eigen_pc1 <- paste0(eigen_pc1$percent,"%")
  eigen_pc2 <- paste0(eigen_pc2$percent,"%")

  #------------- Output & graphic -----------------

  if(isTRUE(plot)){

    p <- pca_fit %>%
      broom::augment(dat_filtered) %>%
      ggplot2::ggplot(ggplot2::aes(x = .fittedPC1, y = .fittedPC2)) +
      ggplot2::geom_point(size = 1.5, colour = "black") +
      ggplot2::labs(title = "Low-dimension representation of time-series",
                    subtitle = "Each point is a time-series whose normalised feature vectors were entered into a PCA.",
                    x = paste0("PC 1"," (",eigen_pc1,")"),
                    y = paste0("PC 2"," (",eigen_pc2,")")) +
      ggplot2::theme_bw() +
      ggplot2::theme(panel.grid.minor = ggplot2::element_blank())

  } else{
    p <- pca_fit %>%
      broom::augment(dat_filtered)
  }
  return(p)
}
