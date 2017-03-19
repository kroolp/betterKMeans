#include "../include/Point.hpp"

Point::Point(std::vector<double> x): x(x){}

Point Point::operator-(Point& otherPoint)
{
  std::vector<double> result;
  result.reserve(this->x.size());
  
  std::transform(this->x.begin(), this->x.end(), otherPoint.x.begin(), 
                 std::back_inserter(result), std::minus<double>());
  
  return Point(result);
}

std::ostream& operator<< (std::ostream& ostream, Point& point) {
  for(std::vector<double>::iterator it = point.x.begin(); it != point.x.end(); it++)
    ostream << *it << " ";

  return ostream;
}