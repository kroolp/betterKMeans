#include <cmath>
#include <limits>
#include "../include/KMeans.hpp"
#include <iostream>

KMeans::KMeans(mat pointsMatrix, int k, double epsilon, int maxIter, int omega, string expression)
:pointsMatrix(pointsMatrix), k(k), epsilon(epsilon), maxIter(maxIter), iterationCount(0),
 omega(omega), expression(expression)
{
  PCA pca(pointsMatrix);
  transformedVector = pca.calculate();
  initClusters();
}

void KMeans::calculate()
{
  do
  {
    iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
    KMeans::interpolateFunctions();
  }while(!canStop());
}

void KMeans::initClusters()
{
  mat shuffledMatrix = shuffle(pointsMatrix);

  for(int i=0; i<k; i++)
  {
    Function* func = getInitFunction();
    rowvec centerPoint = shuffledMatrix.row(i);
    Cluster cluster(centerPoint, func, omega);
    clusters.push_back(cluster);
  }
}

void KMeans::setPointsIntoCluster()
{
  clearClusters();

  double minDistance;
  Cluster* cluster;

  for(int i=0; i<pointsMatrix.n_rows; i++)
  {
    rowvec point = pointsMatrix.row(i);
    double transformedPoint = transformedVector.row(i).max();
    minDistance = numeric_limits<double>::max();
    int clusterIndex= -1;

    for(int j=0; j<clusters.size(); j++)
    {
      rowvec centerPoint = clusters[j].centerPoint;
      double distance = clusters[j].calculateDistance(point, transformedPoint);

      if(minDistance >= distance)
      {
        minDistance = distance;
        clusterIndex = j;
      }
    }

    clusters[clusterIndex].points.push_back(point);
    clusters[clusterIndex].transformedPoints.push_back(transformedPoint);
  }
}

void KMeans::setNewCenters()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].setNewCenter();
}

void KMeans::interpolateFunctions()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].interpolateFunction();
}

bool KMeans::canStop()
{
  return errorSum() < epsilon || iterationCount > maxIter;
}

double KMeans::errorSum()
{
  double result = 0.0;

  for(int i=0; i<clusters.size(); i++)
    result += clusters[i].errorSum();

  return result;
}

void KMeans::clearClusters()
{
  for(int i=0; i<clusters.size(); i++)
  {
    clusters[i].points.clear();
    clusters[i].transformedPoints.clear();
  }
}

Function* KMeans::getInitFunction()
{
  if(expression != "")
    return (new StringFunction(expression));
  else
    return (new ParabolicFunction(pointsMatrix.n_cols - 1));
}
