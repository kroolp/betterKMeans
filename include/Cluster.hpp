#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <vector>
#include <cmath>
#include <RcppArmadillo.h>
#include "./StringFunction.hpp"
#include "./NoLinearInterpolation.hpp"
#include "./PCA.hpp"

using namespace std;
using namespace arma;

class Cluster
{
public:
  Cluster(rowvec centerPoint, string expression = "");
  void setNewCenter();
  void interpolateFunction();
  void calculateBase();
  mat pointsMatrix();

  vector <rowvec> points;
  rowvec centerPoint;
  mat base;
  StringFunction func;

  string expression;
};

#endif
