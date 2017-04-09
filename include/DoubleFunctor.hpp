#ifndef DOUBLE_FUNCTOR_HPP
#define DOUBLE_FUNCTOR_HPP

#include <unsupported/Eigen/NonLinearOptimization>
#include <RcppArmadillo.h>
#include "./Function.hpp"

using namespace arma;

class DoubleFunctor
{
public:

  typedef double Scalar;
  enum {
    InputsAtCompileTime = Eigen::Dynamic,
    ValuesAtCompileTime = Eigen::Dynamic
  };
  typedef Eigen::Matrix<Scalar,InputsAtCompileTime,1> InputType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,1> ValueType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,InputsAtCompileTime> JacobianType;

  int m_inputs, m_values;

  DoubleFunctor(mat matrix, Function& function);

  int operator()(const Eigen::VectorXd &x, Eigen::VectorXd &fvec) const;

  int inputs() const;
  int values() const;

  mat matrix;
  Function& function;
};

#endif
