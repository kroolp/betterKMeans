#include <cmath>
#include <limits>
#include "../include/KMeansService.hpp"
#include "../include/MathHelper.hpp"
#include <iostream>

KMeansService::KMeansService(const NumericMatrix& inputMatrix, int k, double epsilon, int maxIter)
:k(k), epsilon(epsilon), maxIter(maxIter)
{
  for(int i=0; i<inputMatrix.nrow(); i++)
  {
    vector<double> rowVector;

    for(int j=0; j<inputMatrix.ncol(); j++)
      rowVector.push_back(inputMatrix(i,j));

    Point point(rowVector);
    points.push_back(point);
  }
}

void KMeansService::calculate()
{
  initClusters();

  double prevD;
  double currentD = calculateD();
  double energy = numeric_limits<double>::max();;

  for(int i=0; i<maxIter && energy >= epsilon; i++)
  {
    setPointsIntoCluster();
    setNewCenters();

    prevD = currentD;
    currentD = calculateD();
    energy = (prevD - currentD)/currentD;
  }
}

void KMeansService::initClusters()
{
  int* centerIndexes = MathHelper::randomUniq(points.size(), k);
  
  for(int i=0; i<k; i++)
  {
    Point centerPoint = points[centerIndexes[i]];
    Cluster cluster(centerPoint, i);
    clusters.push_back(cluster);
  }
  
  delete [] centerIndexes;
}

void KMeansService::setPointsIntoCluster()
{
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    (*it).points.clear();
  
  for(vector<Point>::iterator it = points.begin(); it != points.end(); it++)
  {
    Point& currentPoint = *it;
    Cluster* c = calculateCluster(currentPoint);
    c->points.push_back(&currentPoint);
  }
}

void KMeansService::setNewCenters()
{
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    (*it).setNewCenter();
}

Cluster* KMeansService::calculateCluster(const Point& point)
{
  double minDistance = numeric_limits<double>::max();
  Cluster* nearestCluster = NULL;
  
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
  {
    Point currentPoint = (*it).centerPoint;
    double distance = 0;
    
    if(distance < minDistance)
    {
      nearestCluster = &(*it);
      minDistance = distance;
    }
  }
  
  return nearestCluster;
}

double KMeansService::calculateD()
{
  double sum = 0;

  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
    sum += (*it).calculateD();
  
  return sum;
}