#include "../include/NoLinearInterpolation.hpp"

NoLinearInterpolation::NoLinearInterpolation(mat matrix, Function& function)
: matrix(matrix), function(function) {}

void NoLinearInterpolation::interpolate()
{
  Eigen::VectorXd x(function.parametersCount);
  x.fill(0);

  DoubleFunctor functor(matrix, function);

  Eigen::NumericalDiff<DoubleFunctor> numDiff(functor);
  Eigen::LevenbergMarquardt<Eigen::NumericalDiff<DoubleFunctor>, double> lm(numDiff);

  lm.parameters.maxfev = 2000;
  lm.parameters.xtol = 1.0e-10;

  lm.minimize(x);
}
