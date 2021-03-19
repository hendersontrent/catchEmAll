#---------------------------------------
# This script sets out to test the core
# functions of the catchEmAll package
#---------------------------------------

#---------------------------------------
# Author: Trent Henderson, 11 March 2021
#---------------------------------------

library(catchEmAll)

# Simulate some data to test

data <- 1 + 0.5 * 1:1000 + arima.sim(list(ma = 0.5), n = 1000)

#----------------
# TEST 1: catch22
#----------------

outs_catch22 <- catch22_all(data)

#----------------------
# TEST 2: catchaMouse16
#----------------------

outs_catchaMouse16 <- catchaMouse16_all(data)

#------------
# TEST 3: all
#------------

outs_all <- catch_all(data)

#----------------------
# TEST 4: normalisation
#----------------------

outs_normed <- normalise_catch(data)

#----------------
# TEST 4: heatmap
#----------------

outs_all <- catch_all(data)
