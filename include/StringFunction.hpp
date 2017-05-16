#ifndef STRING_FUNCTION_HPP
#define STRING_FUNCTION_HPP
#include <algorithm>
#include <string>
#include <RcppArmadillo.h>
#include <RcppEigen.h>
#include "./ext/exprtk.hpp"

using namespace arma;
using namespace std;

class StringFunction
{
  public:
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;
    typedef exprtk::parser_error::type error_t;

    StringFunction(string str_expression);

    double operator()(rowvec variables);
    double operator()(rowvec variables, Eigen::VectorXd parameters);

    string str_expression;

    double* currentVariables;
    double* currentParameters;
    int variablesCount;
    int parametersCount;

    void copyVariables(rowvec variables);
    void copyParameters(Eigen::VectorXd parameters);
};

#endif
