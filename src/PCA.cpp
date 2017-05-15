#include "../include/PCA.hpp"

PCA::PCA(mat matrix): matrix(matrix) {}

mat PCA::calculate()
{
  mat coeff, score;
  vec latent, tsquared;

  princomp(coeff, score, latent, tsquared, cov(matrix));
  return coeff;
}
