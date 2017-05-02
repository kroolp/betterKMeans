#ifndef K_MEANS_BASE_HPP
#define K_MEANS_BASE_HPP
#include <RcppArmadillo.h>
#include "./Cluster.hpp"
#include "./Function.hpp"
#include "./StringFunction.hpp"
#include "./ParabolicFunction.hpp"
#include "./PCA.hpp"

using namespace arma;

class KMeansBase
{
public:

  KMeansBase(mat pointsMatrix, int k, double epsilon, int maxIter, int omega = 1, string expression = "");
  virtual void calculate() = 0;
  virtual double distance(rowvec& point, Cluster& c) = 0;

  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();
  void interpolateFunctions();
  bool canStop();
  double errorSum();
  void clearClusters();

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
