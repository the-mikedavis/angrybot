#include <meArm.h>
#include <Servo.h>

meArm arm;

void setup() {
  arm.begin(11, 10, 9, 6);
  arm.openGripper();
}

void loop() {
  arm.gotoPoint(0, 100, 50);
}
