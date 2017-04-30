#include "Gyro.h"


Gyro::Gyro(int gyroPort, int tempPort){
	this->gyroPort = gyroPort;
	this->tempPort = tempPort;
	lastMicros = 0;
	kal.init(1, 0, 1, 0);// 5, 30, 10, 0 for nothing 1,0,1,0
	analogReadResolution(16);
}

void Gyro::calibrate(long time){
	long startTime = millis();
	long totalTimes = 0;
	long tshift = 0;
	while((long)(millis()-startTime) < time*1000){
		totalTimes ++;
   		tshift += analogRead(gyroPort) - 32768;
    	shift = (double)tshift/(double)totalTimes;
    	Serial.printf("caleb  %f\n", shift);
	}
}

double Gyro::getAngle(){
	return degToRad(this->gyroAngle);
}

double Gyro::getVel(){
	return degToRad(this->gyroVel);
}

double Gyro::degToRad(double degToRad){
	return degToRad * (3.14159 / 180.0);;
}


void Gyro::updateAngle(){
	//double temp = (((analogRead(tempPort) * 5/65536.0)-2.46)*111.11)+25;
	long curMicros = micros(); //analogRead takes about 100 microseconds
    long interval = curMicros - lastMicros;
    if(lastMicros == 0){
    	interval = 0;
    }
    lastMicros = curMicros;
    double vel = analogRead(gyroPort) - 32768 - shift-1;
    double filter = kal.update(vel);

    this->gyroVel = filter;
    gyroAngle += ((filter)*(double)interval)/1000000.0;
    while(gyroAngle < 0) gyroAngle += 360;
    gyroAngle = fmod(gyroAngle, 360);
    	if(gyroAngle > 180){
		gyroAngle = gyroAngle - 360;
	}
	
    Serial.printf("%f \t%f \t %d \t %f\n", vel, filter, interval, gyroAngle);

}