#include "../include/ParabolicFunction.hpp"

ParabolicFunction::ParabolicFunction(int variablesCount)
: variablesCount(variablesCount)
{
  parametersCount = 2 * variablesCount + 1;
}

double ParabolicFunction::operator()(rowvec variables)
{
  return calculate(variables);
}

double ParabolicFunction::operator()(rowvec variables, Eigen::VectorXd parameters)
{
  (*this).parameters = parameters;

  return calculate(variables);
}

double ParabolicFunction::calculate(rowvec variables)
{
  double result = 0.0;

  for(int i=0; i<variablesCount; i++)
  {
    result += parameters(i) * pow(variables(i), 2)
              + parameters(variablesCount + i) * variables(i);
  }
  
  result += parameters(parametersCount - 1);

  return result;
}
