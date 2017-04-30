#include <TimerOne.h> 
#include <Kalman.h>

double gyroAngle = 0;
double botAngle = 0;
double vel;
long tshift = 0;
double shift = 0;
long totalTime = 0;
double filter = 0;
long lastMicros;
long calebTime;

Kalman Kal;

void setup() {
  
  Kal.init(1, 0, 1, 0);// 5, 30, 10, 0 for nothing 1,0,1,0
  analogReadResolution(16);
  shift = analogRead(A20) - 32768;
  delay(1000);
  lastMicros = micros();
 // Timer1.initialize(100);

  //Timer1.attachInterrupt(caleb);
  //delay(2000);
  Kal.update(0);
  //Timer1.detachInterrupt();
  //Timer1.attachInterrupt(timerIsr);

  while(millis() < 10000){
    caleb();
  }
  lastMicros = micros();
  calebTime = lastMicros;
  while(1){
    updateAngle();
  }
  


}

void loop() {


}

void caleb(){
    totalTime ++;
    tshift += analogRead(A20) - 32768;
    shift = (double)tshift/(double)totalTime;
    Serial.printf("caleb  %f\n", shift);
}

void updateAngle(){
    long curMicros = micros(); //analogRead takes about 100 microseconds
    long interval = curMicros - lastMicros;
    lastMicros = curMicros;
    vel = analogRead(A20) - 32768 - shift;
    filter = Kal.update(vel);
    double temp = (((analogRead(A19) * 5/65536.0)-2.46)*111.11)+25;
    gyroAngle += ((double)(filter + temp*0.15)/1000000)*((double)interval);

    Serial.printf("%f \t%f \t %d\t %f\t %f\t %f\n", vel, filter,interval , gyroAngle, temp, shift);
    //delay(1);
    
}

