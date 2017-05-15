#include "../include/Cluster.hpp"

Cluster::Cluster(rowvec centerPoint, string expression)
  : centerPoint(centerPoint), expression(expression), base(mat(centerPoint.n_cols, centerPoint.n_cols)), func(StringFunction(expression))
{
  Eigen::VectorXd parameters(func.parametersCount);
  rowvec variables(func.variablesCount);

  base.fill(0);
  parameters.fill(0);
  variables.fill(0);

  func(variables, parameters);
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
  mat points = pointsMatrix();
  if(points.n_rows < func.variablesCount + 1)
    return;

  NoLinearInterpolation noLinearInterpolation(pointsMatrix(), func);
  noLinearInterpolation.interpolate();
}

void Cluster::calculateBase()
{
  mat points = pointsMatrix();
  if(points.n_rows < base.n_cols)
    return;

  PCA pca(pointsMatrix());
  base = pca.calculate();
}

mat Cluster::pointsMatrix()
{
  arma::mat matrix(points.size(), centerPoint.size());
  for(int i=0; i<points.size(); i++)
    matrix.row(i) = points[i];

  return matrix;
}
