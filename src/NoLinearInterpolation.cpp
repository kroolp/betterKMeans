#include "../include/NoLinearInterpolation.hpp"

NoLinearInterpolation::NoLinearInterpolation(mat matrix, StringFunction& function)
: matrix(matrix), function(function) {}

void NoLinearInterpolation::interpolate()
{
  cout<<"start NoLinearInterpolation"<<endl;
  Eigen::VectorXd x(function.parametersCount);
  x.fill(0);

  DoubleFunctor functor(matrix, function);
  
  Eigen::NumericalDiff<DoubleFunctor> numDiff(functor);
  Eigen::LevenbergMarquardt<Eigen::NumericalDiff<DoubleFunctor>, double> lm(numDiff);

  lm.parameters.maxfev = 100;
  lm.parameters.xtol = 1.0e-3;

  lm.minimize(x);
  cout<<"end NoLinearInterpolation"<<endl;
}
