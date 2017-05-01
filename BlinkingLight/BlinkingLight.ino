#include <Gyro.h>
#include <Controller.h>
#include <PID.h>

#define kp 20
#define ki 0
#define kd 0.1

#define LED1 4
#define LED2 13
#define ISR1 26
#define ISR2 27
#define ISR3 28
#define ISR4 29
#define ISR5 30
#define ISR6 31

volatile long lastMicros;
volatile int LT = 0;
volatile int RT = 0;
volatile int LH = 0;
volatile int LV = 0;
volatile int RH = 0;
volatile int RV = 0;




void setup() {

  Gyro gyro(A22,A4);
  PID pidr(kp, ki, kd, 2, 1, 84); // 84 center
  PID pidl(kp, ki, kd, 3, -1, 84);
  Controller controller(pidr, pidl);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  digitalWrite(LED2, HIGH);
  gyro.calibrate(5);
  digitalWrite(LED2, LOW);

  // pin 26-31
  attachInterrupt(ISR1, ISR1LT, CHANGE);
  attachInterrupt(ISR2, ISR2RT, CHANGE);
  attachInterrupt(ISR3, ISR3LH, CHANGE);
  attachInterrupt(ISR4, ISR4LV, CHANGE);
  attachInterrupt(ISR5, ISR5RV, CHANGE);
  attachInterrupt(ISR6, ISR6RH, CHANGE);

  while(1){
    while(RT<10 || micros() - lastMicros > 12000){
      Serial.printf("%d\n",micros() - lastMicros);
      pidr.stop();
      pidl.stop();
      delay(10);
    }
    gyro.updateAngle((LT-500)*0.1 + 455);
    double angle = gyro.getAngle();

    //Serial.printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",LT,RT,LV,LH,RV,RH);
    double vScale = sqrt(RV*RV+RH*RH)*3;
    double rotS = LV * 0.1;
    double targetDir = atan2(RV,-RH);
    double angleAdjust = angle - targetDir;
  
    controller.update(rotS, vScale,gyro.getVel(), angleAdjust);
    
    Serial.printf("%f\t%f\n",gyro.getVel(),rotS);
    //Serial.printf("%f\t%f\t%f\t%f\t%f\n",rotS, targetDir, vScale, angleAdjust, analogRead(A2));

  
    if(abs(angle) < 3.14/4){
      digitalWrite(LED1, HIGH);
    } else {
      digitalWrite(LED1, LOW);
    }
    

  }

}

void loop() { 
}

void ISR1LT(){
  if(digitalRead(ISR1)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    LT = max(dif - 10, 0);
  }
}

void ISR2RT(){
  if(digitalRead(ISR2)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    RT = max(dif - 10, 0);
  }
}

void ISR3LH(){
  if(digitalRead(ISR3)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    LH = dif-514;
  }
}

void ISR4LV(){
  if(digitalRead(ISR4)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    LV = max(dif - 250, 0);
  }
}

void ISR5RV(){
  if(digitalRead(ISR5)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    dif -= 519;
    if(abs(dif) <10) dif = 0;
    RV = dif;
  }
}

void ISR6RH(){
  if(digitalRead(ISR6)){
    lastMicros = micros();
  } else{
    long dif = micros() - lastMicros - 1000;
    dif -= 509;
    if(abs(dif) <10) dif = 0;
    RH = dif;
  }
}





