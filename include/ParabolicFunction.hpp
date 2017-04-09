#ifndef PARABOLIC_FUNCTION_HPP
#define PARABOLIC_FUNCTION_HPP
#include <RcppArmadillo.h>
#include "./Function.hpp"

using namespace arma;
using namespace std;

class ParabolicFunction: public Function
{
  public:
    ParabolicFunction(int variablesCount);

    double operator()(rowvec variables);
    double operator()(rowvec variables, Eigen::VectorXd parameters);

    Eigen::VectorXd parameters;
    int variablesCount;

    double calculate(rowvec variables);
};

#endif
