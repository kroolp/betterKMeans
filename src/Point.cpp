#include "../include/Point.hpp"

Point::Point(vector<double> x)
  : x(x)
{}

double Point::squareDistance(const Point& otherPoint)
{
  double sum = 0;
  
  for(int i=0; i<x.size(); i++)
    sum += pow(x[i] - otherPoint.x[i], 2);
  
  return sum;
}