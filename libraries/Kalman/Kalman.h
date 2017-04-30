#pragma once

class Kalman {
	private:
		double q; //process noise covariance
		double r; //measurement noise covariance
		double x; //value
		double p; //estimation error covariance
		double k; //kalman gain

	public:
		Kalman();
		void init(double q, double r, double p, double intial_value);
		double update(double measurement);
};