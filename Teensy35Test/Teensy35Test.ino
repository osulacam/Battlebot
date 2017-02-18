#include <PWMServoFast.h>

PWMServo servo1;
int pos = 0;    // variable to store the servo positio

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  analogReadResolution(16);

  //pinMode(1,OUTPUT);
  servo1.attach(2, 750, 2000, 50); //analog pin 0
  //servo1.setMaximumPulse(2000);
  //servo1.setMinimumPulse(700);

  //servo2.attach(15); //analog pin 1
  //Serial.begin(19200);
  //Serial.println("Ready");
}


void loop() {
  // read the input on analog pin 0:
  int sensorValue1 = analogRead(A20);
  int sensorValue2 = analogRead(A2);
  // print out the value you read:
  Serial.print(sensorValue1);
  Serial.print(" ");
  Serial.println(sensorValue2);
  delay(50);
  /*for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(75);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(75);                       // waits 15ms for the servo to reach the position
  }*/
}
