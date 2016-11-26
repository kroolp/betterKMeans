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
  
  KMeansService(const NumericMatrix& inputMatrix, int k);
  void calculate();
  
  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();

  Cluster* calculateCluster(const Point& p);
  
  vector<Point> points;
  int k;
  vector <Cluster> clusters;
};

#endif