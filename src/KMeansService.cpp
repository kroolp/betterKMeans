#include <cmath>
#include <limits>
#include "../include/KMeansService.hpp"
#include "../include/MathHelper.hpp"

KMeansService::KMeansService(const NumericMatrix& inputMatrix, int k)
:k(k)
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
    Cluster* c = calculateCluster(*it);
    c->points.push_back(*it);
  }
}

double KMeansService::calculateDistance(const Point& a, const Point& b)
{
  double sum = 0;
  
  for(int i=0; i<a.x.size(); i++)
    sum += pow(a.x[i] - b.x[i], 2);
  
  return sqrt(sum);
}

Cluster* KMeansService::calculateCluster(const Point& point)
{
  double minDistance = numeric_limits<double>::max();
  Cluster* nearestCluster = NULL;
  
  for(vector<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++)
  {
    Point currentPoint = (*it).centerPoint;
    double distance = calculateDistance(currentPoint, point);
    
    if(distance < minDistance)
    {
      nearestCluster = &(*it);
      minDistance = distance;
    }
  }
  
  return nearestCluster;
}
