#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <vector>
#include <RcppArmadillo.h>
#include "./Function.hpp"

using namespace std;
using namespace arma;

class Cluster
{
public:
  Cluster(rowvec centerPoint, Function* func);
  void setNewCenter();
  double errorSum();
  mat pointsMatrix();

  vector <rowvec> points;
  rowvec centerPoint;

  Function* func;
};

#endif
