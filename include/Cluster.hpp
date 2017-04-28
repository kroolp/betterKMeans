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
  Cluster(rowvec centerPoint, Function* func, int omega);
  void setNewCenter();
  void interpolateFunction();
  double errorSum();
  double calculateDistance(rowvec point, double transformedPoint);
  mat pointsMatrix();
  int omega;

  vector <rowvec> points;
  vector <double> transformedPoints;
  rowvec centerPoint;

  Function* func;
};

#endif
