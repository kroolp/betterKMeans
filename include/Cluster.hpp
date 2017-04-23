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
  Cluster(rowvec centerPoint, Function* func, vec& transformedVector);
  void setNewCenter();
  void interpolateFunction();
  double errorSum();
  mat pointsMatrix();

  vector <rowvec> points;
  rowvec centerPoint;

  Function* func;
  vec& transformedVector;
};

#endif
