#include "../include/KMeans.hpp"
#include "../include/KOMeans.hpp"
#include "../include/BetterKMeans.hpp"

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

  return Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = kMeans.labels,
    Rcpp::Named("errors") = kMeans.errors
  );
}

// [[Rcpp::export]]
Rcpp::List kOMeans(arma::mat inputMatrix, int k, double epsilon, int maxIter, arma::vec omega)
{
  KOMeans kOMeans(inputMatrix, k, epsilon, maxIter, omega);
  kOMeans.calculate();

  mat resultMatrix(k, inputMatrix.n_cols);
  cube bases(inputMatrix.n_cols, inputMatrix.n_cols, k);

  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = kOMeans.clusters[i].centerPoint;
    bases.slice(i) = kOMeans.clusters[i].eigenVectors;
  }

  return Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = kOMeans.labels,
    Rcpp::Named("errors") = kOMeans.errors,
    Rcpp::Named("bases") = bases
  );
}

// [[Rcpp::export]]
Rcpp::List betterKMeans(arma::mat inputMatrix, int k, double epsilon, int maxIter, arma::vec omega, std::string expression, arma::mat drawPoints = mat(0, 0))
{
  BetterKMeans betterKMeans(inputMatrix, k, epsilon, maxIter, omega, expression);
  betterKMeans.calculate();

  mat resultMatrix(k, inputMatrix.n_cols);
  cube eigenVectors(inputMatrix.n_cols, inputMatrix.n_cols, k);
  cube eigenValues(inputMatrix.n_cols, 1, k);
  cube resutlToDraw(drawPoints.n_rows, drawPoints.n_cols +1, k);

  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = betterKMeans.clusters[i].centerPoint;
    eigenVectors.slice(i) = betterKMeans.clusters[i].eigenVectors;
    eigenValues.slice(i) = mat(betterKMeans.clusters[i].eigenValues);
    
    mat drawClusterPoints(drawPoints.n_rows, drawPoints.n_cols +1);
    
    for(int j=0; j<drawPoints.n_rows; j++)
    {
      double funcResult = betterKMeans.clusters[i].func(drawPoints.row(j));
      
      for(int k=0; k<drawPoints.n_cols; k++)
      {
        drawClusterPoints.row(j).col(k) = drawPoints.row(j).col(k);
      }
      
      drawClusterPoints.row(j).col(drawPoints.n_cols) = funcResult;
    }
    
    resutlToDraw.slice(i) = drawClusterPoints;
  }
  
  return Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = betterKMeans.labels,
    Rcpp::Named("errors") = betterKMeans.errors,
    Rcpp::Named("eigenVectors") = eigenVectors,
    Rcpp::Named("eigenValues") = eigenValues,
    Rcpp::Named("pointsToDraw") = resutlToDraw
  );
}
