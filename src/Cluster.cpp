#include "../include/Cluster.hpp"

Cluster::Cluster(rowvec centerPoint): centerPoint(centerPoint){}

void Cluster::setNewCenter()
{
  centerPoint = mean(pointsMatrix());
}

double Cluster::errorSum()
{
  double result = 0.0;
  
  for(int i=0; i<points.size(); i++)
    result += pow(norm(points[i] - mean(points[i])), 2);
  
  return result;
}

mat Cluster::pointsMatrix()
{
  arma::mat matrix(points.size(), centerPoint.size());
  for(int i=0; i<points.size(); i++)
    matrix.row(i) = points[i];
  
  return matrix;
}