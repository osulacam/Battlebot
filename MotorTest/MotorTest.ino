#include <PWMServo.h>



PWMServo servo1;
PWMServo servo2;

void setup() {
  servo1.attach(2);
  servo2.attach(3);

  servo2.write(50);

  delay(10000);

   //servo2.write(82);
}

void loop() {
  // put your main code here, to run repeatedly:

}
