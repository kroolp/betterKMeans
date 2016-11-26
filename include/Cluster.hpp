#ifndef CLUSTER_HPP
#define CLUSTER_HPP
#include <Rcpp.h>
#include <vector>
#include "../include/Point.hpp"

using namespace Rcpp;

class Cluster
{
public:
  Cluster(Point centerPoint, int id);
  
  std::vector <*Point> points;
  Point centerPoint;
  int id;
};

#endif