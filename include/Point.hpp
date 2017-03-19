#ifndef POINT_HPP
#define POINT_HPP
#include <Rcpp.h>

class Point
{
public:

  Point(std::vector<double> x);
  Point operator-(Point& otherPoint);
  
  std::vector<double> x;
};

std::ostream& operator<< (std::ostream& ostream, Point& point);

#endif