#include <PWMServo.h>



PWMServo servo1;
PWMServo servo2;

void setup() {
  servo1.attach(2);
  servo2.attach(3);

  servo1.write(90);
  servo2.write(90);

  delay(1000);

  servo1.write(97);
  servo2.write(97);

  delay(3000);

  servo1.write(90);
  servo2.write(90);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
