#include "Kalman.h"

Kalman::Kalman() {

} 

void Kalman::init(double q, double r, double p, double intial_value){
  this->q = q; // proccess noise 0.01
  this->r = r; // measurement noise //0.1
  this->p = p; //estimation error covarience //50
  this->x = intial_value; // 0
}

double Kalman::update(double measurement)
{
  //prediction update
  //omit x = x
  p = p + q;

  //measurement update
  k = p / (p + r);
  x = x + k * (measurement - x);
  p = (1 - k) * p;
  return x;
}