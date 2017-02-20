#include <TimerOne.h> 

double gyroAngle = 0;
int vel;
long tshift;
double shift;
long totalTime = 0;

void setup() {
  
  
  analogReadResolution(16);
  shift = analogRead(A20) - 32768;

  
  Timer1.initialize(1000);

  Timer1.attachInterrupt(caleb);
  delay(5000);
  Timer1.detachInterrupt();
  Timer1.attachInterrupt(timerIsr);


}

void loop() {

}
void caleb(){
    totalTime ++;
    tshift += analogRead(A20) - 32768;
    shift = tshift/totalTime;
}

void timerIsr(){
    vel = analogRead(A20) - 32768 - shift;
    gyroAngle += vel/1000.0;
    Serial.printf("%d \t %f\n", vel, gyroAngle);
   
    
}

