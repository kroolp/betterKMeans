#ifndef SQUARED_EUCLIDEAN_METRIC_HPP
#define SQUARED_EUCLIDEAN_METRIC_HPP
#include <Rcpp.h>
#include "../include/Metric.hpp"
#include "../include/Point.hpp"

class SquaredEuclideanMetric: public Metric
{
public:
  
  double distance(Point a, Point b);
};

#endif