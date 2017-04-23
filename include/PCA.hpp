#ifndef PCA_HPP
#define PCA_HPP
#include <RcppArmadillo.h>

using namespace arma;
using namespace std;

class PCA
{
  public:
    PCA(mat matrix);

    vec* calculate();

    mat matrix;
};

#endif
