#include <TimerOne.h> 

double gyroAngle = 0;
int vel;

void setup() {
  Timer1.initialize(1000);
  Timer1.attachInterrupt(timerIsr);
  int vel = 0;
  analogReadResolution(16);


}

void loop() {

}

void timerIsr(){
    vel = analogRead(A20) - 32768;
    gyroAngle += vel/1000.0;
    Serial.printf("%d \t %f", vel, gyroAngle);
   
    
}

