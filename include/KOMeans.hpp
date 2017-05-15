#ifndef K_O_MEANS_HPP
#define K_O_MEANS_HPP

#include "./KMeansBase.hpp"

class KOMeans: public KMeansBase
{
  public:
    KOMeans(mat pointsMatrix, int k, double epsilon, int maxIter, vec omega);
    void calculate();
    double distance(rowvec& point, Cluster& cluster);
};

#endif
