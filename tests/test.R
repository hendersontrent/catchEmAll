#---------------------------------------
# This script sets out to test the core
# functions of the catchEmAll package
#---------------------------------------

#---------------------------------------
# Author: Trent Henderson, 11 March 2021
#---------------------------------------

library(catchEmAll)
library(dplyr)
library(magrittr)

# Simulate some data to test

data <- 1 + 0.5 * 1:1000 + arima.sim(list(ma = 0.5), n = 1000)

# TEST 1: catch22

outs_catch22 <- catch22_all(data)

# TEST 2: catchaMouse16

outs_catchaMouse16 <- catchaMouse16_all(data)

# TEST 3: all

outs_all <- catch_all(data)

# TEST 4: normalisation

load("helpers/sample.Rda")

test_scaler <- function(method = c("z-score", "Sigmoid", "RobustSigmoid", "MinMax", "MeanSubtract")){
  df <- trial %>%
    group_by(names) %>%
    mutate(values = normalise_catch(values, method = method)) %>%
    ungroup()

  return(df)
}

scale_test_z <- test_scaler(method = "z-score")
scale_test_sigmoid <- test_scaler(method = "Sigmoid")
scale_test_rsigmoid <- test_scaler(method = "RobustSigmoid")
scale_test_minmax <- test_scaler(method = "MinMax")
scale_test_meansub <- test_scaler(method = "MeanSubtract")

# Test 4: PCA

plot_low_dimension(trial, is_normalised = TRUE, id_var = "unique_id", plot = TRUE)
plot_low_dimension(trial, is_normalised = TRUE, id_var = "unique_id", plot = FALSE)
