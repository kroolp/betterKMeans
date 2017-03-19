#ifndef METRIC_HPP
#define METRIC_HPP
#include <Rcpp.h>
#include "../include/Point.hpp"

class Metric
{
public:
  
  virtual double distance(Point a, Point b) = 0;
};

#endif