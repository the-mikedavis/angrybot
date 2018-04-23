#include <meArm.h>
#include <Servo.h>

meArm arm(
    180, 21, -pi/2, pi/2,     // Base
    102, 15, pi/4, 3*pi/4,    // Shoulder
    148, 106, 0, -pi/4,       // Elbow
    70, 125, pi/2, 0);        // Gripper

void setup() {
  arm.begin(11, 10, 9, 6);
  arm.closeGripper();
  arm.gotoPoint(0, 100, 50);
}

void loop() {
  /*
  //Go up and left to grab something
  arm.gotoPoint(-80,100,140);
  arm.closeGripper();
  //Go down, forward and right to drop it
  arm.gotoPoint(70,200,10);
  arm.openGripper();
  //Back to start position
  arm.gotoPoint(0,100,50);
  */
  delay(1000);
}
