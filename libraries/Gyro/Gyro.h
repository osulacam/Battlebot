#pragma once

#include <TimerOne.h> 
#include <Kalman.h>

class Gyro {
	private:
		Kalman kal;
		double shift = 0;
		double gyroAngle = 0;
		double gyroVel = 0;
		int gyroPort;
		int tempPort;
		long lastMicros;
		double degToRad(double deg); //j82C

	public:
		Gyro(int gyroPort, int tempPort);
		void calibrate(long time);
		double getAngle();
		double getVel();
		void updateAngle();

};