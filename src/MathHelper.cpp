#include <cmath>
#include <cstdlib>
#include "../include/MathHelper.hpp"
#include <iostream>

int* MathHelper::randomUniq(int n, int m)
{
  int arr[n];
  for(int i=0; i<n; i++)
    arr[i] = i;
  
  for(int i=0; i<m; i++)
    std::swap(arr[n-1-i], arr[std::rand()%(n-i)]);
  
  int* result = new int[m];
  
  for(int i=n-m; i<n; i++)
    result[i-(n-m)] = arr[i];
  
  return result;
}
