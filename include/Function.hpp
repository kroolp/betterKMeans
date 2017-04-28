#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <RcppArmadillo.h>
#include <RcppEigen.h>

using namespace arma;

class Function
{
  public:
    virtual double operator()(rowvec variables) = 0;
    virtual double operator()(rowvec variables, Eigen::VectorXd parameters) = 0;

    int parametersCount;
};

#endif
