#ifndef POINT_HPP
#define POINT_HPP
#include <Rcpp.h>
#include <vector>

using namespace std;
using namespace Rcpp;

class Point
{
public:

  Point(vector<double> x);
  
  double squareDistance(const Point& b);
  vector<double> x;
};

#endif