
# catchEmAll

CAnonical Time-series CHaracteristics for multiple domains - an
implementation for `R` written as a package to calculate time series
features from [catch22](https://github.com/chlubba/catch22),
[catchaMouse16](https://github.com/DynamicsAndNeuralSystems/catchaMouse16),
and other reduced-redundancy feature sets.

## Installation

*Coming to CRAN soon… Stay posted\!*

You can also install `catchEmAll` from GitHub using the following:

``` r
devtools::install_github("hendersontrent/catchEmAll")
```

## Motivation

The highly comparative time-series analysis approach to temporal data is
one of a data-drive, field agnostic perspective. Pioneered largely
through [Ben Fulcher’s](http://www.benfulcher.com) `MATLAB` toolbox
[`hctsa`](https://github.com/benfulcher/hctsa), this approached has
proven effective in detecting signal from noise, classifying groups, and
performing regression tasks. Since `MATLAB` is proprietary software, the
barrier to broader adoption of this approach is one largely of the
available tools. This package, `catchEmAll`, aims to bridge some of this
gap, by providing convenience functions for the user that automatically
calculate different sets of features on any input time series. All of
the features exist within the larger \>7,700 set that exists in `hctsa`.

## Available functions

There are three core functions in `catchEmAll` so far (where `ts` is a
numerical time-series input vector):

1.  `catch22_all()`
2.  `catchaMouse16_all()`
3.  `catch_all()`

The first two functions (`catch22_all()` and `catchaMouse16_all()`)
automatically calculates individual summary statistics for each of the
time-series features included in their respective sets. If you want to
run all feature calculations in both sets at once, you can use the third
function `catch_all_unique()` to achieve this.

### Individual feature calculations

If you do not want to or need to run the entire sets of `catch22_all()`
or `catchaMouse16_all()`, you can also access the individual feature
calculations as their unique function names, for example
`SC_FluctAnal_2_rsrangefit_50_1_logi_prop_r1()`.

## Future directions

Additional time series feature sets are intended to be added to
`catchEmAll`. This may include coding features from existing `R`
packages such as [`feasts`](https://feasts.tidyverts.org) and
[`tsfeatures`](https://cran.r-project.org/web/packages/tsfeatures/vignettes/tsfeatures.html)
in `C` or `C++` for computational efficiency and ease-of-comparison on
feature-space tasks such as classification and regression.

## Authorship notes

Original `catch22` features coded in `C` by Carl H. Lubba and original
`catchaMouse16` features coded in `C` by Imran Alam.
