#include "../include/Cluster.hpp"

Cluster::Cluster(rowvec centerPoint, Function* func, int omega)
: centerPoint(centerPoint), func(func), omega(omega)
{
  Eigen::VectorXd initParameters(2 * (centerPoint.n_cols - 1) + 1);
  initParameters.fill(0);

  (*(this->func))(centerPoint, initParameters);
}

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

double Cluster::errorSum()
{
  double result = 0.0;

  for(int i=0; i<points.size(); i++)
    result += calculateDistance(points[i], transformedPoints[i]);

  return result;
}

double Cluster::calculateDistance(rowvec point, double transformedPoint)
{
  double center = sum(centerPoint.t());
  return (omega * pow(norm(point - centerPoint), 2.0) + (1 - omega) * ((*(this->func))(point) - point.row(point.n_rows - 1))).max();
}

mat Cluster::pointsMatrix()
{
  arma::mat matrix(points.size(), centerPoint.size());
  for(int i=0; i<points.size(); i++)
    matrix.row(i) = points[i];

  return matrix;
}
