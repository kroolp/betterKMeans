#ifndef K_MEANS_SERVICE_HPP
#define K_MEANS_SERVICE_HPP
#include <Rcpp.h>
#include "../include/Cluster.hpp"
#include <vector>

using namespace std;
using namespace Rcpp;

class KMeansService
{
public:
  
  KMeansService(const NumericMatrix& inputMatrix, int k, double epsilon, int maxIter);
  void calculate();
  
  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();

  Cluster* calculateCluster(const Point& p);
  double calculateD();
  
  vector<Point> points;
  vector <Cluster> clusters;

  int k;
  double epsilon;
  int maxIter;
};

#endif