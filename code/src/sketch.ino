#include <meArm.h>
#include <Servo.h>
#define PING 7
#define LIMIT 120  // mm
#define LOOK 300 //ms

void scan();
void rush();
void stateMachine();

long mm = 0l;
float angle;

/*
meArm arm(
    180, 21, -pi/2, pi/2,     // Base
    102, 15, pi/4, 3*pi/4,    // Shoulder
    148, 106, 0, -pi/4,       // Elbow
    70, 125, pi/2, 0);        // Gripper
    */
meArm arm(
    180, 0, -pi/2, pi/2,     // Base
    168, 78, pi/4, 3*pi/4,    // Shoulder
    141, 111, 0, -pi/4,       // Elbow
    70, 101, pi/2, 0);        // Gripper

void setup() {
  arm.begin(11, 10, 9, 6);
  arm.closeGripper();
  arm.gotoPointCylinder(0, 100, 50);
  Serial.begin(9600);
}

void loop() {
  Serial.print(mm);
  Serial.println(" mm.");
  stateMachine();
}

//  decide where to go based on the state
//  could be written more succintly, but this has room for growth
void stateMachine() {
  if (mm >= LIMIT) scan();
  else rush();
}

void scan () {
  int i;
  angle = -pi/4;
  for (i = 0; i < 3; i++) {
    arm.gotoPointCylinder(angle, 100, 50);
    long duration;
    pinMode(PING, OUTPUT);
    digitalWrite(PING, LOW);
    delayMicroseconds(2);
    digitalWrite(PING, HIGH);
    delayMicroseconds(5);
    digitalWrite(PING, LOW);

    pinMode(PING, INPUT);
    duration = pulseIn(PING, HIGH);
    mm = duration / 29 / 2 * 10;

    if (mm < LIMIT) return; // break to attack

    angle += pi / 4;
    delay(LOOK);
  }
}

void rush() {
  arm.openGripper();
  delay(LOOK);
  arm.closeGripper();
  delay(LOOK);
  /*
  int x, y;
  x = mm * sin(angle);
  y = mm * cos(angle);
  if (arm.isReachable(x, y, 100)) {
    arm.gotoPoint(x, y, 100);
    delay(LOOK);
    arm.gotoPointCylinder(angle, 100, 50);
    delay(LOOK);
  } else Serial.println("Not reachable!");
  */
  mm = 30000;
}
