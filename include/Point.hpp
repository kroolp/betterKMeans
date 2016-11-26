#ifndef POINT_HPP
#define POINT_HPP
#include <Rcpp.h>

using namespace Rcpp;

class Point
{
public:

  Point(const NumericVector& x);
  
  NumericVector x;
};

#endif