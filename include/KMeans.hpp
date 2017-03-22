#ifndef K_MEANS_HPP
#define K_MEANS_HPP
#include <Rcpp.h>
#include "../include/Cluster.hpp"
#include <vector>

using namespace std;
using namespace Rcpp;

class KMeans
{
public:
  
  KMeans(const vector<Point>& points, int k, double epsilon, int maxIter);
  void calculate();
  
  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();
  bool canStop();
  double errorSum();
  
  vector<Point> points;
  vector<Cluster> clusters;

  int k;
  double epsilon;
  int maxIter;
  int iterationCount;
};

#endif