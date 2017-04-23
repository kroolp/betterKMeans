#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <vector>
#include <RcppArmadillo.h>
#include "./Function.hpp"
#include "./NoLinearInterpolation.hpp"

using namespace std;
using namespace arma;

class Cluster
{
public:
  Cluster(rowvec centerPoint, Function* func, int omega);
  void setNewCenter();
  void interpolateFunction();
  double errorSum();
  mat pointsMatrix();
  int omega;

  vector <rowvec> points;
  vector <double> transformedPoints;
  rowvec centerPoint;

  Function* func;
};

#endif
