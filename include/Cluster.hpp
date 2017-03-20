#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <Rcpp.h>
#include <vector>
#include "../include/Point.hpp"
#include "../include/EuclideanMath.hpp"

using namespace std;
using namespace Rcpp;

class Cluster
{
public:
  Cluster(Point& centerPoint);
  void setNewCenter();
  double errorSum();
  
  vector <Point*> points;
  Point centerPoint;
};

#endif