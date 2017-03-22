#include <Rcpp.h>
#include "../include/KMeans.hpp"
using namespace Rcpp;

vector<Point> numericMatrixToPoints(NumericMatrix& matrix)
{
  vector<Point> points;
  
  for(int i=0; i<matrix.nrow(); i++)
  {
    vector<double> rowVector;
    
    for(int j=0; j<matrix.ncol(); j++)
      rowVector.push_back(matrix(i,j));
    
    Point point(rowVector);
    points.push_back(point);
  }
  
  return points;
}

NumericMatrix clustersToNumericMatrix(vector<Cluster>& clusters, int dimension)
{
  NumericMatrix clustersMatrix(clusters.size(), dimension);

  for(int i=0; i<clusters.size(); i++)
  {
    vector<double>& x = clusters[i].centerPoint.x;
    for(int j=0; j<x.size(); j++)
    {
      clustersMatrix(i, j) = x[j];
    }
  }
  
  return clustersMatrix;
}

// [[Rcpp::export]]
NumericMatrix kmeans(NumericMatrix inputMatrix, int k, double epsilon, int maxIter)
{
  vector<Point> points = numericMatrixToPoints(inputMatrix);
  
  KMeans kMeans(points, k, epsilon, maxIter);
  kMeans.calculate();
  
  NumericMatrix resultMatrix = clustersToNumericMatrix(kMeans.clusters, inputMatrix.ncol());
  
  return resultMatrix;
}