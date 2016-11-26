#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <Rcpp.h>
#include <vector>
#include "../include/Point.hpp"

using namespace std;
using namespace Rcpp;

class Cluster
{
public:
  Cluster(Point centerPoint, int id);
  void setNewCenter();
  double calculateD();
  
  vector <Point*> points;
  Point centerPoint;
  int id;
};

#endif