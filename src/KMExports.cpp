#include "../include/KMeans.hpp"

// [[Rcpp::export]]
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
}