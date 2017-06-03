#include "../include/KOMeans.hpp"

KOMeans::KOMeans(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega)
: KMeansBase(pointsMatrix, k, epsilon, maxIter, omega) {}

void KOMeans::calculate()
{
  do
  {
    iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
    calculateBases();
  }while(!canStop());
}

double KOMeans::distance(rowvec& point, Cluster& cluster)
{
  double result = 0.0;

  rowvec shiftedVector = point - cluster.centerPoint;
  double toCenterDistance = pow(norm(shiftedVector), 2);

  for(int i=0; i<pointsMatrix.n_cols + 1; i++)
  {
    double currentOmega = omega.row(i).max();
    double sum = 0.0;

    for(int j=0; j<i; j++)
      sum += pow(dot(shiftedVector, cluster.eigenVectors.row(j)), 2);

    result += currentOmega * (toCenterDistance - sum);
  }

  return result;
}
