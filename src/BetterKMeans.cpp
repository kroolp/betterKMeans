#include "../include/BetterKMeans.hpp"

BetterKMeans::BetterKMeans(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega, string expression)
: KMeansBase(pointsMatrix, k, epsilon, maxIter, omega, expression) {}

void BetterKMeans::calculate()
{
  do
  {
    iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
    calculateBases();
    interpolateFunctions();
  }while(!canStop());
}

double BetterKMeans::distance(rowvec& point, Cluster& cluster)
{
  vec shiftedVector = (point - cluster.centerPoint).t();
  rowvec transformedvector = (cluster.base * shiftedVector).t();
  double fromCenterDistance = (pow(norm(transformedvector), 2));
  double functionValue = cluster.func(point);
  double fromFunctionDistance = pow((functionValue - point.col(point.n_cols - 1).max()), 2);

  return omega.row(0).max() * fromCenterDistance + (1.0 - omega.row(0).max()) * fromFunctionDistance;
}
