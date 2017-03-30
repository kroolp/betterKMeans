#include <cmath>
#include <limits>
#include "../include/KMeans.hpp"
#include <iostream>

KMeans::KMeans(mat pointsMatrix, int k, double epsilon, int maxIter)
:pointsMatrix(pointsMatrix), k(k), epsilon(epsilon), maxIter(maxIter), iterationCount(0)
{
  initClusters();
}

void KMeans::calculate()
{
  do
  {
    iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
  }while(!canStop());
}

void KMeans::initClusters()
{
  mat shuffledMatrix = shuffle(pointsMatrix);
  
  for(int i=0; i<k; i++)
  {
    rowvec centerPoint = shuffledMatrix.row(i);
    Cluster cluster(centerPoint);
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
    minDistance = numeric_limits<double>::max();
    int clusterIndex= -1;

    for(int j=0; j<clusters.size(); j++)
    {
      rowvec centerPoint = clusters[j].centerPoint;
      double distance = pow(norm(point - centerPoint), 2);

      if(minDistance >= distance)
      {
        minDistance = distance;
        clusterIndex = j;
      }
    }
    
    clusters[clusterIndex].points.push_back(point);
  }
}

void KMeans::setNewCenters()
{
  for(int i=0; i<clusters.size(); i++)
    clusters[i].setNewCenter();
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
    clusters[i].points.clear();
}