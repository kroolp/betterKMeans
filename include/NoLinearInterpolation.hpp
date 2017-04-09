#ifndef NO_LINEAR_INTERPOLATION_HPP
#define NO_LINEAR_INTERPOLATION_HPP
#include <RcppArmadillo.h>
#include "./Function.hpp"
#include "./DoubleFunctor.hpp"

using namespace arma;
using namespace std;

class NoLinearInterpolation
{
  public:
    NoLinearInterpolation(mat matrix, Function& function);
    void interpolate();

    mat matrix;
    Function& function;
};

#endif
