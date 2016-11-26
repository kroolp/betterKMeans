#include <Rcpp.h>
#include "../include/KMeansService.hpp"
#include <vector>
#include <iostream>
using namespace Rcpp;

// [[Rcpp::export]]
void testowa(NumericMatrix matrix, int k) {
  KMeansService kMeansService(matrix, k);
  kMeansService.initClusters();
  
  std::vector <Cluster>::iterator it;
  for(it = kMeansService.clusters.begin(); it != kMeansService.clusters.end(); it++)
  {
    for(int i=0; i<(*it).centerPoint.x.size(); i++)
    {
      std::cout<< (*it).centerPoint.x[i] <<", ";
    }
    
    std::cout<<std::endl;
  }
}