// there are 513 steps per revolution

#include <Stepper.h>

int pin1 = 12;
int pin2 = 11;
int pin3 = 10;
int pin4 = 9;

Stepper motor(513, pin1, pin2, pin3, pin4);

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  Serial.begin(9600);
  motor.setSpeed(20);
}

void loop() {
  if(Serial.available() > 0) {
    int steps = Serial.parseInt();
    Serial.print(steps);
    motor.step(steps);
  }
}
