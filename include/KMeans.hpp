#ifndef K_MEANS_HPP
#define K_MEANS_HPP
#include <RcppArmadillo.h>
#include "./Cluster.hpp"
#include "./Function.hpp"
#include "./StringFunction.hpp"
#include "./ParabolicFunction.hpp"
#include "./PCA.hpp"

using namespace arma;

class KMeans
{
public:

  KMeans(mat pointsMatrix, int k, double epsilon, int maxIter, int omega = 1, string expression = "");
  void calculate();

  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();
  void interpolateFunctions();
  bool canStop();
  double errorSum();
  void clearClusters();
  Function* getInitFunction();

  mat pointsMatrix;
  vec transformedVector;
  vector<Cluster> clusters;

  int k;
  double epsilon;
  int maxIter;
  int iterationCount;
  int omega;
  string expression;
};

#endif
