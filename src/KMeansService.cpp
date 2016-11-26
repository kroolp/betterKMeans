#include <cmath>
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

    inputData.push_back(rowVector);
  }
}

double KMeansService::calculateDistance(const Point& a, const Point& b)
{
  double sum = 0;
  
  for(int i=0; i<a.x.size(); i++)
    sum += pow(a.x[i] - b.x[i], 2);
  
  return sqrt(sum);
}

void KMeansService::initClusters()
{
  int* centerIndexes = MathHelper::randomUniq(inputData.size(), k);

  for(int i=0; i<k; i++)
  {
    vector<double> vector = inputData[centerIndexes[i]];
    Point centerPoint(vector);
    Cluster cluster(centerPoint);
    clusters.push_back(cluster);
  }
  
  delete [] centerIndexes;
}
