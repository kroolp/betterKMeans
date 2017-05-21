#ifndef PCA_HPP
#define PCA_HPP
#include <RcppArmadillo.h>

using namespace arma;
using namespace std;

class PCA
{
  public:
    PCA(mat matrix);

    void calculate();

    mat matrix;
    mat eigenVectors;
    vec eigenValues;
};

#endif
