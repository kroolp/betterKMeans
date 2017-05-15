#ifndef K_MEANS_BASE_HPP
#define K_MEANS_BASE_HPP
#include <RcppArmadillo.h>
#include "./Cluster.hpp"
#include "./StringFunction.hpp"

using namespace arma;

class KMeansBase
{
public:

  KMeansBase(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega, string expression = "");
  virtual void calculate() = 0;
  virtual double distance(rowvec& point, Cluster& c) = 0;

  void initClusters();
  void setPointsIntoCluster();
  void setNewCenters();
  void interpolateFunctions();
  void calculateBases();
  bool canStop();
  double errorSum();
  void clearClusters();

  mat pointsMatrix;
  vec labels;
  vec errors;
  vector<Cluster> clusters;

  int k;
  double epsilon;
  int maxIter;
  int iterationCount;
  vec omega;
  string expression;
};

#endif
