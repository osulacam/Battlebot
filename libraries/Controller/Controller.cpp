#include "Controller.h"
#include "math.h"
#include "PID.h"

Controller::Controller(PID pidr, PID pidl){
	this->pidl = pidl;
	this->pidr = pidr;
}

 void Controller::update(double rotS, double vScale, double curVel ,double angleAdjust){
  double linS = cos(angleAdjust) * vScale;
  this->rVel = linS + rotS;
  this->lVel = linS - rotS;
  double Lff = sin(angleAdjust)*vScale;
  double Rff = sin(angleAdjust)*vScale;

  pidl.setFF(Lff);
  pidr.setFF(Rff);
  pidl.setVel(-rotS);
  pidr.setVel(rotS);
  drive(curVel);
  //Serial.printf("%f\t%f\n",rotS,Lff);
 }


 void Controller::drive(double curVel){
 	pidl.runServo(curVel);
 	pidr.runServo(curVel);
 }

