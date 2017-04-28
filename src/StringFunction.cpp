#include "../include/StringFunction.hpp"

StringFunction::StringFunction(string str_expression)
{
  variablesCount = parametersCount = 0;

  for(;str_expression.find("X" + to_string(variablesCount + 1)) != string::npos; variablesCount++);
  for(;str_expression.find("B" + to_string(parametersCount + 1)) != string::npos; parametersCount++);

  currentVariables = new double[variablesCount];
  currentParameters = new double[parametersCount];

  symbol_table_t symbol_table;

  for(int i=0; i<variablesCount; i++)
    symbol_table.add_variable("X" + to_string(i + 1), currentVariables[i]);

  for(int i=0; i<parametersCount; i++)
    symbol_table.add_variable("B" + to_string(i + 1), currentParameters[i]);

  expression.register_symbol_table(symbol_table);

  parser_t parser;
  parser.compile(str_expression,expression);
}

double StringFunction::operator()(rowvec variables)
{
  copyVariables(variables);

  return expression.value();
}

double StringFunction::operator()(rowvec variables, Eigen::VectorXd parameters)
{
  copyVariables(variables);
  copyParameters(parameters);

  return expression.value();
}

void StringFunction::copyVariables(rowvec variables)
{
  for(int i=0; i<variablesCount; i++)
    currentVariables[i] = variables[i];
}

void StringFunction::copyParameters(Eigen::VectorXd parameters)
{
  for(int i=0; i<parametersCount; i++)
    currentParameters[i] = parameters[i];
}
