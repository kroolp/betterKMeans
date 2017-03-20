#include "../include/Cluster.hpp"

Cluster::Cluster(Point& centerPoint): centerPoint(centerPoint){}

void Cluster::setNewCenter()
{
  vector<double>& v = centerPoint.x;
  fill(v.begin(), v.end(), 0.0);
  
  for(vector<Point*>::iterator pointIt=points.begin(); pointIt != points.end(); pointIt++)
  {
    vector<double>& currentVector = (**pointIt).x;

    for(int i=0; i<v.size(); i++)
      v[i] += currentVector[i];
  }
  
  for(int i=0; i<v.size(); i++)
    v[i] /= points.size();
}

double Cluster::errorSum()
{
  double result = 0.0;
  
  for(vector<Point*>::iterator it=points.begin(); it != points.end(); it++)
    result += EuclideanMath::squaredDistance(**it, this->centerPoint);
  
  return result;
}