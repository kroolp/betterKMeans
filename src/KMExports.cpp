#include "../include/KMeans.hpp"
#include "../include/KOMeans.hpp"
#include "../include/BetterKMeans.hpp"

#include <RcppArmadillo.h>
using namespace arma;
using namespace std;

#include "../include/PCA.hpp"
//' K-Means clustering
//'
//' @description
//' It's traditional clustering method without any modifications.
//' 
//' It has own plot method.
//' 
//' @param inputMatrix N-dimensional matrix with data to clustering
//' @param k The number of clusters
//' @param epsilon Max squared error to stop clustering
//' @param maxIter Max iteration number to stop clustering
//' 
//' @return The instance of kmeans class which is list with:
//' 
//' * centers - Center of the each cluster
//' 
//' * labels - Label of each point, which indicates cluster of this point
//' 
//' * errors - Mean error of each cluster (sum of distance divided by number of points in the cluster)
//' 
//' * inputMatrix - copy of matrix from function parameters
//' @examples
//' library(KM)
//' 
//' ## chinese_father is dataset with 2d representation of the word "Father" in Chinese writing
//' inputMatrix <- chinese_father
//' 
//' result <- kmeans(inputMatrix, 3, 0.01, 30)
//' plot(result)
// [[Rcpp::export]]
Rcpp::List kmeans(arma::mat inputMatrix, int k, double epsilon, int maxIter)
{
  KMeans kMeans(inputMatrix, k, epsilon, maxIter);
  kMeans.calculate();

  mat resultMatrix(k, inputMatrix.n_cols);
  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = kMeans.clusters[i].centerPoint;
  }
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = kMeans.labels,
    Rcpp::Named("errors") = kMeans.errors,
    Rcpp::Named("inputMatrix") = inputMatrix
  );
  
  out.attr("class") = "kmeans";

  return out;
}

//' K-Omega-Means clustering
//'
//' @description
//' It's modification traditional K-Means clustering method, which use n-dimensional omega input and cluster bases
//' to calculate distances.
//' 
//' It has own plot method.
//' 
//' @param inputMatrix N-dimensional matrix with data to clustering
//' @param k The number of clusters
//' @param epsilon Max squared error to stop clustering
//' @param maxIter Max iteration number to stop clustering
//' @param omega N-dimensional vector with weights from 0.0 to 1.0
//' 
//' @return The instance of kOmeans class which is list with:
//' 
//' * centers - Center of the each cluster
//' 
//' * labels - Label of each point, which indicates cluster of this point
//' 
//' * errors - Mean error of each cluster (sum of distance divided by number of points in the cluster)
//' 
//' * eigenVectors - Eigen vector of each cluster, calculated from covariance of points in the cluster.
//' 
//' * eigenValues - Eigen value of each cluster, calculated from  covariance of points in the cluster.
//' 
//' * inputMatrix - copy of matrix from function parameters
//' @examples
//' library(KM)
//' 
//' ## small_letter_f is dataset with 2d representation of the small letter "f"
//' inputMatrix <- small_letter_f
//' 
//' result <- kOmeans(inputMatrix, 4, 0.01, 50, c(5.0, 0.5))
//' plot(result)
// [[Rcpp::export]]
Rcpp::List kOmeans(arma::mat inputMatrix, int k, double epsilon, int maxIter, arma::vec omega)
{
  KOMeans kOMeans(inputMatrix, k, epsilon, maxIter, omega);
  kOMeans.calculate();

  mat resultMatrix(k, inputMatrix.n_cols);
  cube eigenVectors(inputMatrix.n_cols, inputMatrix.n_cols, k);
  cube eigenValues(inputMatrix.n_cols, 1, k);

  for(int i=0; i<k; i++)
  {
    resultMatrix.row(i) = kOMeans.clusters[i].centerPoint;
    eigenVectors.slice(i) = kOMeans.clusters[i].eigenVectors;
    eigenValues.slice(i) = mat(kOMeans.clusters[i].eigenValues);
  }
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = kOMeans.labels,
    Rcpp::Named("errors") = kOMeans.errors,
    Rcpp::Named("eigenVectors") = eigenVectors,
    Rcpp::Named("eigenValues") = eigenValues,
    Rcpp::Named("inputMatrix") = inputMatrix
  );
  
  out.attr("class") = "kOmeans";

  return out;
}

//' Better-K-Means clustering
//'
//' @description
//' It's modification traditional K-Means clustering method, which use omega input, cluster bases
//' and no-linear function interpolation to calculate distances.
//' 
//' It has own plot method.
//' 
//' @param inputMatrix N-dimensional matrix with data to clustering
//' @param k The number of clusters
//' @param epsilon Max squared error to stop clustering
//' @param maxIter Max iteration number to stop clustering
//' @param omega The number which is weight from 0.0 to 1.0
//' @param expression String with math expression,
//' which includes parameters symbols (B1,B2...BN) and arguments symbols (X1,X2...XN).
//' @param drawPoints Matrix with points from specific range,
//' if you don't plan to plot result you can ignore this parameter
//' 
//' @return The instance of betterKmeans class which is list with:
//' 
//' * centers - Center of the each cluster
//' 
//' * labels - Label of each point, which indicates cluster of this point
//' 
//' * errors - Mean error of each cluster (sum of distance divided by number of points in the cluster)
//' 
//' * eigenVectors - Eigen vector of each cluster, calculated from covariance of points in the cluster.
//' 
//' * eigenValues - Eigen value of each cluster, calculated from  covariance of points in the cluster.
//' 
//' * pointsToDraw - Result of function of each cluster with drawPoints as arguments.
//' If you don't plan to plot result you can ignore this.
//' 
//' * inputMatrix - copy of matrix from function parameters
//' @examples
//' library(KM)
//' 
//' ## large_letter_G is dataset with 2d representation of the large letter "G"
//' inputMatrix <- large_letter_G
//' 
//' ## "(X1^2)*B1+X1*B2+B3" - Quadratic function
//' result <- betterKmeans(inputMatrix, 5, 0.01, 10, c(0.5), "(X1^2)*B1+X1*B2+B3", as.matrix(seq(-2, 2, length.out = 400)))
//' plot(result)
// [[Rcpp::export]]
Rcpp::List betterKmeans(arma::mat inputMatrix, int k, double epsilon, int maxIter, arma::vec omega, std::string expression, arma::mat drawPoints = mat(0, 0))
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
        drawClusterPoints.row(j).col(k) = drawPoints.row(j).col(k);
      
      drawClusterPoints.row(j).col(drawPoints.n_cols) = funcResult;
    }
    
    resutlToDraw.slice(i) = drawClusterPoints;
  }
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("centers") = resultMatrix,
    Rcpp::Named("labels") = betterKMeans.labels,
    Rcpp::Named("errors") = betterKMeans.errors,
    Rcpp::Named("eigenVectors") = eigenVectors,
    Rcpp::Named("eigenValues") = eigenValues,
    Rcpp::Named("pointsToDraw") = resutlToDraw,
    Rcpp::Named("inputMatrix") = inputMatrix
  );
  
  out.attr("class") = "betterKmeans";
  
  return out;
}
