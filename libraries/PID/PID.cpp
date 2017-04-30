#include "PID.h"

PID::PID(double kp, double ki, double kd, int pin, int dir){
	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
	this->dir = dir;
	servo.attach(pin,1240,1704, 100);
}

PID::PID(){
	this->kp = 0;
	this->ki = 0;
	this->kd = 0;	
}

void PID::setVel(double vel){
	this->targetVel = vel;
}


double PID::getPow(){
	return targetVel;
}

void PID::stop(){
	servo.write(90);
}

void PID::setFF(double feedForward){
	FF = feedForward;//targetVel*10;
}

void PID::runServo(double curVel){
	double E = targetVel - curVel; 
	double acc = curVel - lastVel;
	lastVel = curVel;


	double output = kp * E +  kd * acc;
	motorPow = dir*(output)/10.0 + 90; //add ff

	servo.write(motorPow);
}
