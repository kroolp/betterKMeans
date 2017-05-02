#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <vector>
#include <cmath>
#include <RcppArmadillo.h>
#include "./Function.hpp"
#include "./StringFunction.hpp"
#include "./ParabolicFunction.hpp"
#include "./NoLinearInterpolation.hpp"

using namespace std;
using namespace arma;

class Cluster
{
public:
  Cluster(rowvec centerPoint, string expression = "");
  void setNewCenter();
  void interpolateFunction();
  mat pointsMatrix();

  vector <rowvec> points;
  rowvec centerPoint;

  string expression;
  Function* func;
};

#endif
