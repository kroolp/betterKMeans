#include "../include/Cluster.hpp"

Cluster::Cluster(rowvec centerPoint, Function* func, vec& transformedVector)
: centerPoint(centerPoint), func(func), transformedVector(transformedVector)
{
  Eigen::VectorXd initParameters;
  initParameters.fill(0);

  (*(this->func))(centerPoint, initParameters);
}

void Cluster::setNewCenter()
{
  centerPoint = mean(pointsMatrix());
}

void Cluster::interpolateFunction()
{
  NoLinearInterpolation noLinearInterpolation(pointsMatrix(), *func);
  noLinearInterpolation.interpolate();
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
