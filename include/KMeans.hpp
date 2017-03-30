#ifndef K_MEANS_HPP
#define K_MEANS_HPP
#include <RcppArmadillo.h>
#include "../include/Cluster.hpp"

using namespace arma;

class KMeans
{
public:
  
  KMeans(mat pointsMatrix, int k, double epsilon, int maxIter);
  void calculate();
  
  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();
  bool canStop();
  double errorSum();
  void clearClusters();
  
  mat pointsMatrix;
  vector<Cluster> clusters;

  int k;
  double epsilon;
  int maxIter;
  int iterationCount;
};

#endif