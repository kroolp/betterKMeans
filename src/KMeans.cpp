#include "../include/KMeans.hpp"

KMeans::KMeans(mat pointsMatrix, int k, double epsilon, int maxIter)
: KMeansBase(pointsMatrix, k, epsilon, maxIter, vec(1)) {}

void KMeans::calculate()
{
  do
  {
    iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
  }while(!canStop());
}

double KMeans::distance(rowvec& point, Cluster& cluster)
{
  return pow(norm(point - cluster.centerPoint), 2);
}
