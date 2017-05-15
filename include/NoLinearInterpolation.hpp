#ifndef NO_LINEAR_INTERPOLATION_HPP
#define NO_LINEAR_INTERPOLATION_HPP
#include <RcppArmadillo.h>
#include "./DoubleFunctor.hpp"

using namespace arma;
using namespace std;

class NoLinearInterpolation
{
  public:
    NoLinearInterpolation(mat matrix, StringFunction& function);
    void interpolate();

    mat matrix;
    StringFunction& function;
};

#endif
