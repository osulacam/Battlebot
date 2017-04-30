#pragma once
#include <PID.h>
#include <TimerOne.h> 

#define kp 1
#define ki 0
#define kd 0

class Controller {
	private:
		double rVel;
		double lVel;
		double angle;
		double vel;
		double lastVel;
		double acc;
		PID pidr;
		PID pidl;

	public:
		Controller(PID pidr, PID pidl);
		void update(double rotS, double vScale,double curVel, double angleAdjust);
		void drive(double curVel);
};