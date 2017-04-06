#include "../include/KMeans.hpp"
#include "../include/ext/exprtk.hpp"
#include <RcppEigen.h>
#include <RcppArmadillo.h>
#include <unsupported/Eigen/NonLinearOptimization>
using namespace arma;
using namespace std;
/*#include <unsupported/Eigen/NumericalDiff>

template<typename _Scalar, int NX = Eigen::Dynamic, int NY = Eigen::Dynamic>
struct Functor
{
  typedef _Scalar Scalar;
  enum {
    InputsAtCompileTime = NX,
    ValuesAtCompileTime = NY
  };
  typedef Eigen::Matrix<Scalar,InputsAtCompileTime,1> InputType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,1> ValueType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,InputsAtCompileTime> JacobianType;

  int m_inputs, m_values;

  Functor() : m_inputs(InputsAtCompileTime), m_values(ValuesAtCompileTime) {}
  Functor(int inputs, int values) : m_inputs(inputs), m_values(values) {}

  int inputs() const { return m_inputs; }
  int values() const { return m_values; }

};

struct my_functor : Functor<double>
{
  my_functor(void): Functor<double>(2,3) {}
  int operator()(const Eigen::VectorXd &x, Eigen::VectorXd &fvec) const
  {
    fvec(0) = 38 - pow(2.0, x(0)) * 5.0 - x(1);
    fvec(1) = 190 - pow(4.0, x(0)) * 3.0 - x(1);
    fvec(2) = -2 - pow(2.0, x(0)) * 0.0 - x(1);

    return 0;
  }
};

// [[Rcpp::export]]
void test()
{
  Eigen::VectorXd x(2);
  x(0) = 2.0;
  x(1) = 3.0;
  std::cout << "x: " << x << std::endl;

  my_functor functor;
  Eigen::NumericalDiff<my_functor> numDiff(functor);
  Eigen::LevenbergMarquardt<Eigen::NumericalDiff<my_functor>,double> lm(numDiff);
  lm.parameters.maxfev = 2000;
  lm.parameters.xtol = 1.0e-10;
  std::cout << lm.parameters.maxfev << std::endl;

  int ret = lm.minimize(x);
  std::cout << lm.iter << std::endl;
  std::cout << ret << std::endl;

  std::cout << "x that minimizes the function: " << x << std::endl;

  std::cout << "press [ENTER] to continue " << std::endl;
}

arma::mat kMeans(arma::mat inputMatrix, int k, double epsilon, int maxIter)
{
  KMeans kMeans(inputMatrix, k, epsilon, maxIter);
  kMeans.calculate();

  mat resultMatrix(k, inputMatrix.n_cols);
  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = kMeans.clusters[i].centerPoint;
  }

  return resultMatrix;
}*/

#include "../include/StringFunction.hpp"
// [[Rcpp::export]]
void test()
{
  string exp = "(B1^B2) * sin(X1) + B2*tan(X2) - X1*B1";

  Eigen::VectorXd B(2);
  B(0) = 2.0;
  B(1) = 3.0;
  rowvec X;
  X << 0.3 << 0.7;
  StringFunction function(exp);
  cout<<function(X, B)<<endl;
  cout<<function(X)<<endl;
 // rowvec X2;
//  X2 << 0.5;
//  cout<<function(X2, B)<<endl;
}

/*
void test()
{
  typedef exprtk::symbol_table<double> symbol_table_t;
  typedef exprtk::expression<double>     expression_t;
  typedef exprtk::parser<double>             parser_t;

  std::string expression_str = "(sin(x)*(tan(x)^2))^(-1)";

  double x = 0.3;

  // Register x with the symbol_table
  symbol_table_t symbol_table;
  symbol_table.add_variable("x",x);

  // Instantiate expression and register symbol_table
  expression_t expression;
  expression.register_symbol_table(symbol_table);

  // Instantiate parser and compile the expression
  parser_t parser;
  parser.compile(expression_str,expression);

  double result = 0.0;

  // Evaluate and print result for when x = 1.1
  result = expression.value();
  printf("Result1: %10.5f\n",result);

  // Update/modify the value of x
  x = 2.2;

  // Evaluate and print result for when x = 2.2
  result = expression.value();
  printf("Result2: %10.5f\n",result);
}*/
