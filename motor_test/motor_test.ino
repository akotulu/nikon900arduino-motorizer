#include <Stepper.h>

//
int revolution_steps=200;

// initialize stepper library on pins 12 through 9
Stepper stepper(revolution_steps, 12, 11, 10, 9);

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(revolution_steps);
}
