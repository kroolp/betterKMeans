#include "../include/EuclideanMath.hpp"

double EuclideanMath::squaredNorm(Point& a)
{
  double result = 0.0;
  
  for(std::vector<double>::iterator it = a.x.begin(); it != a.x.end(); it++)
    result += pow(*it, 2); 
  
  return result;
}

double EuclideanMath::norm(Point& a)
{
  return sqrt(squaredNorm(a));
}

double EuclideanMath::squaredDistance(Point& a, Point& b)
{
  Point c = a - b;
  return squaredNorm(c);
}