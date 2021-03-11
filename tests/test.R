#---------------------------------------
# This script sets out to test the core
# functions of the catchEmAll package
#---------------------------------------

#---------------------------------------
# Author: Trent Henderson, 11 March 2021
#---------------------------------------

library(catchEmAll)

# Simulate some data to test

timeseries <- 1 + 0.5 * 1:100 + arima.sim(list(ma = 0.5), n = 100)

#----------------
# TEST 1: catch22
#----------------

outs_catch22 <- catch22_all(timeseries)

#----------------------
# TEST 2: catchaMouse16
#----------------------

outs_catchaMouse16 <- catchaMouse16_all(timeseries)

#------------
# TEST 3: all
#------------

outs_all <- catch_all(timeseries)
