#ifndef K_MEANS_SERVICE_HPP
#define K_MEANS_SERVICE_HPP
#include <Rcpp.h>
#include "../include/Cluster.hpp"

using namespace Rcpp;

class KMeansService
{
public:
  
  KMeansService(const NumericMatrix& inputData, int k);
  void initClusters();

private:
  double calculateDistance(const Point& a, const Point& b);
  
  NumericMatrix inputData;
  int k;
  std::vector <Cluster> clusters;
};

#endif