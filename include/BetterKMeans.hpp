#ifndef BETTER_K_MEANS_HPP
#define BETTER_K_MEANS_HPP

#include "./KMeansBase.hpp"

class BetterKMeans: public KMeansBase
{
  public:
    BetterKMeans(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega, string expression);
    void calculate();
    double distance(rowvec& point, Cluster& cluster);
};

#endif
