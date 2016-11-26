#include "../include/Cluster.hpp"

Cluster::Cluster(Point centerPoint, int id)
  : centerPoint(centerPoint), id(id)
{}

void Cluster::setNewCenter()
{
  vector<double>& v = centerPoint.x;
  fill(v.begin(), v.end(), 0);
  
  for(vector<Point*>::iterator it=points.begin(); it != points.end(); it++)
  {
    vector<double>& currentVector = (**it).x;

    for(int i=0; i<v.size(); i++)
      v[i] += currentVector[i];
  }
  
  for(int i=0; i<v.size(); i++)
    v[i] /= points.size();
}