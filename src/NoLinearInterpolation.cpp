#include "../include/NoLinearInterpolation.hpp"

NoLinearInterpolation::NoLinearInterpolation(mat matrix, StringFunction& function)
: matrix(matrix), function(function) {}

void NoLinearInterpolation::interpolate()
{
  cout<<"Eigen::VectorXd x(function.parametersCount);"<<endl;
  Eigen::VectorXd x(function.parametersCount);
  cout<<"x.fill(0);"<<endl;
  x.fill(0);

  cout<<"DoubleFunctor functor(matrix, function);"<<endl;
  DoubleFunctor functor(matrix, function);

  cout<<"Eigen::NumericalDiff<DoubleFunctor> numDiff(functor);"<<endl;
  Eigen::NumericalDiff<DoubleFunctor> numDiff(functor);
  cout<<"Eigen::LevenbergMarquardt<Eigen::NumericalDiff<DoubleFunctor>, double> lm(numDiff);"<<endl;
  Eigen::LevenbergMarquardt<Eigen::NumericalDiff<DoubleFunctor>, double> lm(numDiff);

  cout<<"lm.parameters.maxfev = 2000;"<<endl;
  lm.parameters.maxfev = 2000;
  cout<<"lm.parameters.xtol = 1.0e-10;"<<endl;
  lm.parameters.xtol = 1.0e-10;

  cout<<"lm.minimalize(x);"<<endl;
  lm.minimize(x);
  cout<<"lm.minimalize(x); finish"<<endl;
}
