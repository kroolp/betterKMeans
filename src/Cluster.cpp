#include "../include/Cluster.hpp"

Cluster::Cluster(rowvec centerPoint, string expression)
: centerPoint(centerPoint), expression(expression) {}

void Cluster::setNewCenter()
{
  if(points.size() > 0)
    centerPoint = mean(pointsMatrix());
  else
    centerPoint.fill(0);
}

void Cluster::interpolateFunction()
{
  NoLinearInterpolation noLinearInterpolation(pointsMatrix(), *func);
  noLinearInterpolation.interpolate();
}

mat Cluster::pointsMatrix()
{
  arma::mat matrix(points.size(), centerPoint.size());
  for(int i=0; i<points.size(); i++)
    matrix.row(i) = points[i];

  return matrix;
}
