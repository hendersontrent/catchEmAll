#' Produce a heatmap matrix of the calculated feature value vectors and each unique time series. Performs automatic hierarchical clustering.
#' @import dplyr
#' @import ggplot2
#' @import tibble
#' @importFrom magrittr %>%
#' @importFrom tidyr pivot_wider
#' @importFrom reshape2 melt
#' @param data a dataframe with at least 2 columns called 'names' and 'values'
#' @param is_normalised a Boolean as to whether the input feature values have already been scaled. Defaults to FALSE
#' @param id_var a string specifyingthe ID variable to group data on (if one exists). Defaults to NULL
#' @return an object of class ggplot that contains the heatmap graphic
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
#' plot_features(outs, is_normalised = FALSE, id_var = "group")
#' }
#'

plot_features <- function(data, is_normalised = FALSE, id_var = NULL){

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

  #------------- Assign ID variable ---------------

  if(is.null(id_var)){
    data <- data %>%
      dplyr::mutate(id = dplyr::row_number())
  } else{
    data <- data %>%
      dplyr::rename(id = dplyr::all_of(id_var))
  }

  #------------- Normalise data -------------------

  if(is_normalised){
    normed1 <- data
  } else{
    normed <- data %>%
      dplyr::select(c(id, names, values)) %>%
      dplyr::group_by(names) %>%
      dplyr::mutate(values = normalise_catch(values)) %>%
      dplyr::ungroup()

    normed1 <- normed %>%
      dplyr::filter(!is.nan(values))

    if(nrow(normed1) != nrow(normed)){
      message("Filtered out rows containing NaNs.")
    }
  }

  #------------- Hierarchical clustering ----------

  dat <- normed1 %>%
    tidyr::pivot_wider(id_cols = id, names_from = names, values_from = values) %>%
    tibble::column_to_rownames(var = "id")

  row.order <- hclust(dist(dat))$order # Hierarchical cluster on rows
  col.order <- hclust(dist(t(dat)))$order # Hierarchical cluster on columns
  dat_new <- dat[row.order, col.order] # Re-order matrix by cluster outputs
  cluster_out <- reshape2::melt(as.matrix(dat_new)) %>% # Turn into dataframe
    dplyr::rename(id = Var1,
           names = Var2)

  #------------- Draw graphic ---------------------

  message("Rendering graphic...")

  p <- cluster_out %>%
    ggplot2::ggplot(ggplot2::aes(x = names, y = id, fill = value)) +
    ggplot2::geom_tile() +
    ggplot2::labs(title = "Heatmap of hierarchically-clustered scaled features and individual time series",
                  x = "Feature",
                  y = "Time series",
                  fill = "Scaled feature value") +
    ggplot2::theme_bw() +
    ggplot2::scale_fill_gradient(low = "#4575b4", high = "#d73027") +
    ggplot2::theme(legend.position = "bottom",
                   axis.text.y = ggplot2::element_blank(),
                   axis.text.x = ggplot2::element_text(angle = 90, hjust = 1))

  return(p)
}
