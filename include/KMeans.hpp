#ifndef K_MEANS_HPP
#define K_MEANS_HPP

#include "./KMeansBase.hpp"

class KMeans: public KMeansBase
{
  public:
    KMeans(mat pointsMatrix, int k, double epsilon, int maxIter);
    void calculate();
    double distance(rowvec& point, Cluster& cluster);
};

#endif
