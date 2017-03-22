#include <cmath>
#include <limits>
#include "../include/KMeans.hpp"
#include "../include/MathHelper.hpp"
#include <iostream>

KMeans::KMeans(const vector<Point>& points, int k, double epsilon, int maxIter)
:points(points), k(k), epsilon(epsilon), maxIter(maxIter), iterationCount(0)
{
  initClusters();
}

void KMeans::calculate()
{
  do
  {
    this->iterationCount++;

    setPointsIntoCluster();
    setNewCenters();
  }while(!canStop());
}

void KMeans::initClusters()
{
  int* centerIndexes = MathHelper::randomUniq(points.size(), k);
  
  for(int i=0; i<k; i++)
  {
    Point centerPoint = points[centerIndexes[i]];
    Cluster cluster(centerPoint);
    clusters.push_back(cluster);
  }
  
  delete [] centerIndexes;
}

void KMeans::setPointsIntoCluster()
{
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    (*it).points.clear();
  
  double minDistance;
  Cluster* cluster;

  for(vector<Point>::iterator pointIt = points.begin(); pointIt != points.end(); pointIt++)
  {
    minDistance = numeric_limits<double>::max();
    cluster = NULL;

    for(vector<Cluster>::iterator clusterIt = clusters.begin(); clusterIt != clusters.end(); clusterIt++)
    {
      Point& centerPoint = (*clusterIt).centerPoint;
      double distance = EuclideanMath::squaredDistance(*pointIt, centerPoint);

      if(minDistance >= distance)
      {
        minDistance = distance;
        cluster = &(*clusterIt);
      }
    }
    
    if(cluster != NULL)
      (*cluster).points.push_back(&(*pointIt));
  }
}

void KMeans::setNewCenters()
{
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    (*it).setNewCenter();
}

bool KMeans::canStop()
{
  return errorSum() < this->epsilon || this->iterationCount > this->maxIter;
}

double KMeans::errorSum()
{
  double result = 0.0;
  
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    result += (*it).errorSum();
  
  return result;
}