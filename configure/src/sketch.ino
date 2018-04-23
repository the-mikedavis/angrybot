#include <Servo.h>

#define BASE 11
#define SHOULDER 9
#define ELBOW 10
#define GRIPPER 6
#define POTN A0

Servo *servo;
int angle = 90;

Servo base, shoulder, elbow, gripper;

void setup() {
  Serial.begin(9600);

  base.attach(BASE);
  servo = &base;
}

void loop() {
  angle = map(analogRead(POTN), 0, 1023, 0, 180);
  servo->write(angle);
  Serial.println(angle);

  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case 'b':
        servo->detach();
        servo = &base;
        servo->attach(BASE);
      break;
      case 'g':
        servo->detach();
        servo = &gripper;
        servo->attach(GRIPPER);
      break;
      case 'e':
        servo->detach();
        servo = &elbow;
        servo->attach(ELBOW);
      break;
      case 's':
        servo->detach();
        servo = &shoulder;
        servo->attach(SHOULDER);
      break;
      default:
      break;
    }
  }
}
