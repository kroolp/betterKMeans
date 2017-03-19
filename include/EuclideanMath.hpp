#ifndef EUCLIDEAN_MATH_HPP
#define EUCLIDEAN_MATH_HPP
#include <Rcpp.h>
#include "../include/Point.hpp"

class EuclideanMath
{
public:
  
  static double squaredNorm(Point& a);
  static double norm(Point& a);
  static double squaredDistance(Point& a, Point& b);
};

#endif