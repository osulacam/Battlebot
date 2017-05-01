#pragma once

#include <PWMServoFast.h>
#include <TimerOne.h> 

class PID{
	private:
		double kp;
		double ki;
		double kd;
		double targetVel;
		double lastVel;
		double FF;
		int dir;
		PWMServo servo;
		double motorPow;
		int center;

	public:
		PID(double kp, double ki, double kd, int pin, int dir, int center);
		PID();
		void setVel(double vel);
		void setFF(double feedForward);
		void runServo(double curVel);
		double getPow();
		void stop();
};