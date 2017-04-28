#include "../include/PCA.hpp"

PCA::PCA(mat matrix): matrix(matrix) {}

vec PCA::calculate()
{
  mat coeff, score;
  vec latent, tsquared;

  princomp(coeff, score, latent, tsquared, matrix);
  return (vec)score.col(0);
}
