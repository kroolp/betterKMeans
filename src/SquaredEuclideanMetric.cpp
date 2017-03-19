#include "../include/SquaredEuclideanMetric.hpp"

double SquaredEuclideanMetric::distance(Point a, Point b)
{
  Point c = a - b;
  double result = 0.0;

  for(std::vector<double>::iterator it = c.x.begin(); it != c.x.end(); it++)
    result += pow(*it, 2); 

  return result;
}