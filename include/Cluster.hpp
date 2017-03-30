#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <vector>
#include <RcppArmadillo.h>

using namespace std;
using namespace arma;

class Cluster
{
public:
  Cluster(rowvec centerPoint);
  void setNewCenter();
  double errorSum();
  mat pointsMatrix();

  vector <rowvec> points;
  rowvec centerPoint;
};

#endif