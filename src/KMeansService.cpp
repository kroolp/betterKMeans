#include <cmath>
#include "../include/KMeansService.hpp"

KMeansService::KMeansService(const NumericMatrix& inputData, int k)
  :inputData(inputData), k(k)
  {}

double KMeansService::calculateDistance(const Point& a, const Point& b)
{
  double sum = 0;
  
  for(int i=0; i<a.x.size(); i++)
    sum += pow(a.x[i] - b.x[i], 2);
  
  return sqrt(sum);
}

void KMeansService::initClusters()
{
  
}
