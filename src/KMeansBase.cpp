#include <cmath>
#include <limits>
#include "../include/KMeansBase.hpp"
#include <iostream>

KMeansBase::KMeansBase(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega, string expression)
:pointsMatrix(pointsMatrix), k(k), epsilon(epsilon), maxIter(maxIter), iterationCount(0),
 omega(omega), expression(expression), labels(vec(pointsMatrix.n_rows)), errors(vec(k))
{
  initClusters();
}

void KMeansBase::initClusters()
{
  mat shuffledMatrix = shuffle(pointsMatrix);

  for(int i=0; i<k; i++)
  {
    rowvec centerPoint = shuffledMatrix.row(i);
    Cluster cluster(centerPoint, expression);
    clusters.push_back(cluster);
  }
}

void KMeansBase::setPointsIntoCluster()
{
  clearClusters();

  double minDistance;
  Cluster* cluster = NULL;

  for(int i=0; i<pointsMatrix.n_rows; i++)
  {
    rowvec point = pointsMatrix.row(i);
    minDistance = numeric_limits<double>::max();
    int clusterIndex= 0;

    for(int j=0; j<clusters.size(); j++)
    {
      double calculatedDistance = distance(point, clusters[j]);

      if(minDistance >= calculatedDistance)
      {
        minDistance = calculatedDistance;
        clusterIndex = j;
      }
    }

    clusters[clusterIndex].points.push_back(point);
    labels.row(i) = clusterIndex + 1;
  }
}

void KMeansBase::setNewCenters()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].setNewCenter();
}

void KMeansBase::interpolateFunctions()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].interpolateFunction();
}

void KMeansBase::calculateBases()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].calculateBase();
}


bool KMeansBase::canStop()
{
  return errorSum() < epsilon || iterationCount > maxIter;
}

double KMeansBase::errorSum()
{
  double result = 0.0;

  for(int i=0; i<clusters.size(); i++)
  {
      for(int j=0; j<clusters[i].points.size(); j++)
      {
        double calculatedDistance = distance(clusters[i].points[j], clusters[i]);
        errors.row(i) += calculatedDistance;
        result += calculatedDistance;
      }
  }

  return result;
}

void KMeansBase::clearClusters()
{
  for(int i=0; i<clusters.size(); i++)
  {
    clusters[i].points.clear();
  }
}
