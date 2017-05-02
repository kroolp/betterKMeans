#include "../include/Function.hpp"
#include "../include/StringFunction.hpp"
#include "../include/ParabolicFunction.hpp"
#include "../include/NoLinearInterpolation.hpp"
#include "../include/KMeans.hpp"

#include <RcppArmadillo.h>
using namespace arma;
using namespace std;

#include "../include/PCA.hpp"
// [[Rcpp::export]]
Rcpp::List kMeans(arma::mat inputMatrix, int k, double epsilon, int maxIter)
{
  KMeans kMeans(inputMatrix, k, epsilon, maxIter);
  kMeans.calculate();
  
  mat resultMatrix(k, inputMatrix.n_cols);
  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = kMeans.clusters[i].centerPoint;
  }

  return Rcpp::List::create(Rcpp::Named("centers") = resultMatrix);
}
