#include "../include/PCA.hpp"

PCA::PCA(mat matrix): matrix(matrix) {}

vec* PCA::calculate()
{
  vec* transformedVector = new vec(matrix.n_rows);
  vec eig_values;
  mat eig_vectors;

  eig_sym(eig_values, eig_vectors, cov(matrix));

  for(int i=0; i<matrix.n_rows; i++)
    (*transformedVector)[i] = sum((matrix.row(i) - mean(matrix)) * eig_vectors.row(eig_vectors.n_rows - matrix.n_rows + i).t());

  return transformedVector;
}
