#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <unsupported/Eigen/NonLinearOptimization>

template<typename _Scalar, int NX = Eigen::Dynamic, int NY = Eigen::Dynamic>
class Functor
{
public:

  typedef _Scalar Scalar;
  enum {
    InputsAtCompileTime = NX,
    ValuesAtCompileTime = NY
  };
  typedef Eigen::Matrix<Scalar,InputsAtCompileTime,1> InputType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,1> ValueType;
  typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,InputsAtCompileTime> JacobianType;
  
  int m_inputs, m_values;
  
  Functor();
  Functor(int inputs, int values);
  
  int inputs() const;
  int values() const;
};

#endif